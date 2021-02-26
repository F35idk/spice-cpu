
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

static int
ngspice_exit_callback(
    int exit_status,
    bool unload_immediately,
    bool exit_on_quit,
    int id,
    void *user_data
)
{
    return 0;
}

static int
ngspice_output_callback(
    char *output_str,
    int id,
    void *user_data
)
{
    if (strstr(output_str, "stderr")) {
        printf("ngspice error: '%s'\n", &output_str[7]);
        if (!strstr(output_str, "gmin"))
            exit(1); // consider the error fatal
    }

    return 0;
}

static void
test(
    // the path to the SPICE netlist
    const char *netlist_path,
    // the path to the '.cmp' file
    const char *cmp_file_path,
    // the labels of the columns in the cmp file representing the various
    // logic inputs/outputs (the cmp file is essentially a truth table)
    const char *input_labels[],
    const char *output_labels[]
)
{
    #define MAX_LABELS 0x100
    #define MAX_LABEL_LEN 6

    // the labels of the SPICE nodes or voltage sources representing logic
    // inputs/outputs (corresponding to the labels in the 'input_labels'
    // and 'output_labels' arrays above)
    char spice_output_labels[MAX_LABELS][MAX_LABEL_LEN + 1] = {0};
    char spice_input_labels[MAX_LABELS][MAX_LABEL_LEN + 1] = {0};

    int cmp_fd;
    int cmp_file_len;
    int cmp_file_pos;
    char *cmp_file;

    for (int i = 0; input_labels[i]; i++) {
        assert(strlen(input_labels[i]) <= MAX_LABEL_LEN);
    }

    for (int i = 0; output_labels[i]; i++) {
        assert(strlen(output_labels[i]) <= MAX_LABEL_LEN);
    }

    printf("simulating '%s'\n", netlist_path);

    // open the cmp file
    cmp_fd = open(cmp_file_path, O_RDONLY);
    cmp_file_len = lseek(cmp_fd, 0, SEEK_END);
    cmp_file = mmap(NULL, cmp_file_len, PROT_READ, MAP_PRIVATE, cmp_fd, 0);
    cmp_file_pos = 0;

    // loop over the labels found in each cell of the first row in the cmp
    // file. prepend a 'v' to the labels representing a logic input and an
    // 'n' to the labels representing a logic output, and store them in
    // 'spice_output_labels' and 'spice_input_labels'. the new labels should
    // match the labels of the corresponding logic input/output nodes/voltage
    // sources in the SPICE netlist we're simulating.
    for (int j = 0, k = 0; cmp_file_pos < cmp_file_len && cmp_file[cmp_file_pos] != '\n';) {
        char *label = NULL;
        int label_len = 0;

        // increment 'cmp_file_pos' until a label (or newline) is found
        while (cmp_file_pos < cmp_file_len
               && (cmp_file[cmp_file_pos] == ' '
                   || cmp_file[cmp_file_pos] == '|'
                   || cmp_file[cmp_file_pos] == '\r')) {
            cmp_file_pos++;
        }

        // increment 'label_len' and 'cmp_file_pos' until end of label is reached
        while (cmp_file_pos < cmp_file_len
               && cmp_file[cmp_file_pos] != ' '
               && cmp_file[cmp_file_pos] != '|'
               && cmp_file[cmp_file_pos] != '\n') {
            label_len++;
            cmp_file_pos++;
        }

        assert(label_len < MAX_LABEL_LEN);

        if (!label_len) {
            // no valid label found - end of line reached
            assert(cmp_file[cmp_file_pos] == '\n');
            break;
        }

        label = &cmp_file[cmp_file_pos - label_len];
        for (int h = 0; input_labels[h] || output_labels[h]; h++) {
            if (input_labels[h] && (int) strlen(input_labels[h]) == label_len
                && !strncmp(label, input_labels[h], label_len)) {
                spice_input_labels[j][0] = 'v';
                spice_input_labels[j][MAX_LABEL_LEN] = 0;
                strncpy(&spice_input_labels[j][1], label, label_len);
                j++;
                break;
            } else if (output_labels[h] && (int) strlen(output_labels[h]) == label_len
                       && !strncmp(label, output_labels[h], label_len)) {
                spice_output_labels[k][0] = 'n';
                spice_output_labels[k][MAX_LABEL_LEN] = 0;
                strncpy(&spice_output_labels[k][1], label, label_len);
                k++;
                break;
            }
        }
    }

    int cmd_len = 7 + strlen(netlist_path) + 1;
    char *source_cmd = calloc(sizeof(char), cmd_len);
    snprintf(source_cmd, cmd_len, "source %s", netlist_path);
    // send source command
    int error = ngSpice_Command(source_cmd);
    free(source_cmd);

    if (error) {
        printf("error when sending command: '%s'\n", source_cmd);
        exit(1);
    }

    // TODO: fix this mess
    // simulate and test the logic inputs/outputs, row by row
    while (++cmp_file_pos < cmp_file_len) {
        // loop over every logic input value in the current row of the cmp file
        for (int j = 0; j < MAX_LABELS && spice_input_labels[j][0]; cmp_file_pos++) {
            // if the current character is ascii zero or one
            if (cmp_file[cmp_file_pos] == '0' || cmp_file[cmp_file_pos] == '1') {
                char alter_cmd[10 + MAX_LABEL_LEN + 1] = {0};
                char input_voltage = cmp_file[cmp_file_pos] == '1' ? '5' : '0';

                // format the 'alter' command to set the right input voltage
                snprintf(alter_cmd, sizeof(alter_cmd),
                         "alter %s = %c", spice_input_labels[j],
                         input_voltage);

                // send the alter command to ngspice
                int error = ngSpice_Command(alter_cmd);
                printf("setting %s = %cV\n", spice_input_labels[j], input_voltage);

                if (error) {
                    printf("error when sending command: '%s'\n", alter_cmd);
                    exit(1);
                }

                j++;
            }
        }

        // end of row should not have been reached yet
        assert(cmp_file[cmp_file_pos] != '\n');

        // simulate
        int error = ngSpice_Command("run");
        if (error) {
            puts("error when sending command: 'run'");
            exit(1);
        }

        // loop over every logic output value in the current
        // row of the cmp file (until end of row is reached)
        for (int j = 0; cmp_file[cmp_file_pos] != '\n'; cmp_file_pos++) {
            if ((cmp_file[cmp_file_pos] == '0' || cmp_file[cmp_file_pos] == '1')
                && j < MAX_LABELS && spice_output_labels[j][0]) {
                vector_info *output_info;
                float output_voltage;

                output_info = ngGet_Vec_Info(spice_output_labels[j]);
                assert(output_info);

                if (!output_info->v_length) {
                    printf("error: output vector '%s' has length zero",
                           output_info->v_name);
                    exit(1);
                }

                output_voltage = output_info->v_realdata[output_info->v_length - 1];
                printf("%s voltage: %fV\n", output_info->v_name, output_voltage);

                // test that the output voltages from the simulation
                // match the logic output given by the cmp file
                if (cmp_file[cmp_file_pos] == '0') {
                    // if logic output should be zero, assert that
                    // the output voltage is less than 1.0V
                    assert(output_voltage < 1.0);
                    printf("correct voltage!\n");
                } else if (cmp_file[cmp_file_pos] == '1') {
                    // if logic output should be one, assert that
                    // the output voltage is more than 4.0V
                    assert(output_voltage > 4.0);
                    printf("correct voltage!\n");
                }

                j++;
            }
        }
    }

    puts("");
    munmap(cmp_file, cmp_file_len);
}

int
main(void)
{
    // initialize ngspice
    ngSpice_Init(ngspice_output_callback, NULL, ngspice_exit_callback,
                 NULL, NULL, NULL, NULL);

    // TODO: ..

    return 0;
}
