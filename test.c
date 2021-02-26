
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
    // the labels of the SPICE nodes or voltage
    // sources representing logic inputs/outputs
    const char *spice_input_labels[],
    const char *spice_output_labels[]
)
{
    int cmp_fd;
    int cmp_file_len;
    int cmp_file_pos;
    char *cmp_file;

    printf("simulating '%s'\n", netlist_path);

    // open the cmp file
    cmp_fd = open(cmp_file_path, O_RDONLY);
    cmp_file_len = lseek(cmp_fd, 0, SEEK_END);
    cmp_file = mmap(NULL, cmp_file_len, PROT_READ, MAP_PRIVATE, cmp_fd, 0);
    cmp_file_pos = 0;

    // skip first line of file (column headers)
    while (cmp_file[cmp_file_pos++] != '\n')
        continue;

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

    // simulate and test the logic inputs/outputs, row by row
    while (++cmp_file_pos < cmp_file_len) {
        // loop over every logic input value in the current row of the cmp file
        for (int j = 0; spice_input_labels[j]; cmp_file_pos++) {
            // if the current character is ascii zero or one
            if (cmp_file[cmp_file_pos] == '0' || cmp_file[cmp_file_pos] == '1') {
                int cmd_len = 10 + strlen(spice_input_labels[j]) + 1;
                char *alter_cmd = calloc(sizeof(char), cmd_len);
                char input_voltage = cmp_file[cmp_file_pos] == '1' ? '5' : '0';

                // format the 'alter' command to set the right input voltage
                snprintf(alter_cmd, cmd_len, "alter %s = %c",
                         spice_input_labels[j], input_voltage);

                // send the alter command to ngspice
                int error = ngSpice_Command(alter_cmd);
                printf("setting %s = %cV\n", spice_input_labels[j], input_voltage);

                if (error) {
                    printf("error when sending command: '%s'\n", alter_cmd);
                    free(alter_cmd);
                    exit(1);
                }

                free(alter_cmd);
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
            if (spice_output_labels[j] && (cmp_file[cmp_file_pos] == '0'
                                           || cmp_file[cmp_file_pos] == '1')) {
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

    test("not/not.sp",
         "not/Not.cmp",
         (const char *[]) { "vin", NULL },
         (const char *[]) { "nout", NULL });

    test("nand/nand.sp",
         "nand/Nand.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test("nor/nor.sp",
         "nor/Nor.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test("and/and.sp",
         "and/And.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test("or/or.sp",
         "or/Or.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test("xor/xor.sp",
         "xor/Xor.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test("mux/mux.sp",
         "mux/Mux.cmp",
         (const char *[]) { "va", "vb", "vsel", NULL },
         (const char *[]) { "nout", NULL });

    test("dmux/dmux.sp",
         "dmux/DMux.cmp",
         (const char *[]) { "vin", "vsel", NULL },
         (const char *[]) { "na", "nb", NULL });

    test("4waymux/4waymux.sp",
         "4waymux/4WayMux.cmp",
         (const char *[]) { "va", "vb", "vc", "vd", "vsel0", "vsel1", NULL },
         (const char *[]) { "nout", NULL });

    test("halfadder/halfadder.sp",
         "halfadder/HalfAdder.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nsum", "ncarry", NULL });

    test("fulladder/fulladder.sp",
         "fulladder/FullAdder.cmp",
         (const char *[]) { "va", "vb", "vc", NULL },
         (const char *[]) { "nsum", "ncarry", NULL });

    return 0;
}
