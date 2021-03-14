
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
        fprintf(stderr, "ngspice error: '%s'\n", &output_str[7]);

        if (strstr(output_str, "Simulation interrupted due to error!"))
            exit(1);
    }

    return 0;
}

static void
init_test(
    // the path to the SPICE netlist
    const char *netlist_path,
    // the path to the '.cmp' file
    const char *cmp_file_path,
    char **out_cmp_file,
    int *out_cmp_file_len
)
{
    int cmp_fd;

    printf("simulating '%s'\n", netlist_path);

    // open the cmp file
    cmp_fd = open(cmp_file_path, O_RDONLY);
    *out_cmp_file_len = lseek(cmp_fd, 0, SEEK_END);
    *out_cmp_file = mmap(NULL, *out_cmp_file_len, PROT_READ, MAP_PRIVATE, cmp_fd, 0);
    close(cmp_fd);

    int cmd_len = 7 + strlen(netlist_path) + 1;
    char *source_cmd = calloc(sizeof(char), cmd_len);
    snprintf(source_cmd, cmd_len, "source %s", netlist_path);
    // send command to open netlist file
    int error = ngSpice_Command(source_cmd);
    free(source_cmd);

    if (error) {
        printf("error when sending command: '%s' - check stderr\n", source_cmd);
        exit(1);
    }

    // delete all previous breakpoints
    error = ngSpice_Command("delete all");
    if (error) {
        puts("error when sending command: 'delete all' - check stderr");
        exit(1);
    }
}

// sends a command to ngspice to alter 'device' with the given 'value'
static void
send_ngspice_alter_cmd(
    const char *device_name,
    const char value
)
{
    int cmd_len = 10 + strlen(device_name) + 1;
    char *alter_cmd = calloc(sizeof(char), cmd_len);

    // format the 'alter' command to set the right device parameter and value
    snprintf(alter_cmd, cmd_len, "alter %s = %c", device_name, value);

    // send the alter command to ngspice
    int error = ngSpice_Command(alter_cmd);
    printf("setting %s = %cV\n", device_name, value);

    if (error) {
        printf("error when sending command: '%s' - check stderr\n", alter_cmd);
        free(alter_cmd);
        exit(1);
    }

    free(alter_cmd);
}

static float
get_ngspice_vector_voltage(const char *vector_name)
{
    vector_info *info;
    float voltage;

    info = ngGet_Vec_Info(vector_name);
    assert(info);

    if (!info->v_length) {
        printf("error: output vector '%s' has length zero - check stderr\n",
               info->v_name);
        exit(1);
    }

    voltage = info->v_realdata[info->v_length - 1];

    return voltage;
}

static void
assert_correct_voltage(
    float voltage,
    char expected_logic_level
)
{
    switch (expected_logic_level) {
        case '0':
            // if logic level should be zero, assert
            // that the voltage is less than 1.0V
            assert(voltage < 1.0);
            printf("correct voltage!\n");
            break;
        case '1':
            // if logic level should be one, assert
            // that the voltage is more than 4.0V
            assert(voltage > 4.0);
            printf("correct voltage!\n");
            break;
        case '?':
            printf("voltage is undefined for these inputs, ignoring value\n");
            break;
        default:
            break;
    }
}

// tests combinational circuits. every input combination given by
// the specified '.cmp' file is tried. after simulating, the
// outputs are tested against the output values given by the cmp
// file. the function exit()s if they do not match
static void
test_combinational(
    // the path to the SPICE netlist
    const char *netlist_path,
    // the path to the '.cmp' file
    const char *cmp_file_path,
    // the labels of the SPICE nodes/voltage sources
    // representing logic inputs/outputs, in the
    // order they appear in the cmp file
    const char *spice_input_labels[],
    const char *spice_output_labels[]
)
{
    char *cmp_file;
    int cmp_file_len;
    int cmp_file_pos;

    init_test(netlist_path, cmp_file_path, &cmp_file, &cmp_file_len);
    cmp_file_pos = 0;

    // skip to first newline (ignore column header)
    while ((cmp_file_pos + 1) < cmp_file_len && cmp_file[++cmp_file_pos] != '\n')
        continue;

    // simulate and test the logic inputs/outputs, row by row
    while (++cmp_file_pos < cmp_file_len) {
        // loop over every logic input value in the current row of the cmp file
        for (int j = 0; spice_input_labels[j]; cmp_file_pos++) {
            // if the current character is ascii zero or one
            if (cmp_file[cmp_file_pos] == '0' || cmp_file[cmp_file_pos] == '1') {
                char input_voltage = cmp_file[cmp_file_pos] == '1' ? '5' : '0';
                send_ngspice_alter_cmd(spice_input_labels[j], input_voltage);

                j++;
            }
        }

        // end of row should not have been reached yet
        assert(cmp_file[cmp_file_pos] != '\n');

        // simulate
        int error = ngSpice_Command("run");
        if (error) {
            puts("error when sending command: 'run' - check stderr");
            exit(1);
        }

        // loop over every logic output value in the current
        // row of the cmp file (until end of row is reached)
        for (int j = 0; cmp_file[cmp_file_pos] != '\n'; cmp_file_pos++) {
            if (spice_output_labels[j] && (cmp_file[cmp_file_pos] == '0'
                                           || cmp_file[cmp_file_pos] == '1')) {
                float output_voltage =
                    get_ngspice_vector_voltage(spice_output_labels[j]);
                printf("%s voltage: %fV\n", spice_output_labels[j], output_voltage);
                // test that the output voltages from the simulation
                // match the logic outputs in the cmp file
                assert_correct_voltage(output_voltage, cmp_file[cmp_file_pos]);
                j++;
            }
        }
    }

    puts("");
    munmap(cmp_file, cmp_file_len);
}

// tests sequential circuits. the first column in a sequential
// circuit cmp file is assumed to represent time
static void
test_sequential(
    const char *netlist_path,
    const char *cmp_file_path,
    const char *spice_input_labels[],
    const char *spice_output_labels[]
)
{
    char *cmp_file;
    int input_output_len;
    char *input_output_values;
    int cmp_file_len;
    int cmp_file_pos;

    init_test(netlist_path, cmp_file_path, &cmp_file, &cmp_file_len);
    cmp_file_pos = 0;

    while ((cmp_file_pos + 1) < cmp_file_len && cmp_file[++cmp_file_pos] != '\n')
        continue;

    input_output_len = cmp_file_len; // more bytes than needed
    input_output_values = calloc(sizeof(char), cmp_file_len - cmp_file_pos);

    // set breakpoints at the right times and gather up
    // all of the input/output values in the cmp file
    for (int i = 0; cmp_file_pos < cmp_file_len; cmp_file_pos++) {
        // skip to the first character that is a number (ascii 0x30-0x39)
        while (cmp_file[cmp_file_pos] < 0x30 || cmp_file[cmp_file_pos] > 0x39)
            cmp_file_pos++;

        // - this character represents the current row's time
        double time = (strtod(&cmp_file[cmp_file_pos], NULL) + 0.1);
        int cmd_len = 30;
        char *break_cmd = calloc(sizeof(char), cmd_len);
        snprintf(break_cmd, cmd_len, "stop when time = %fus", time);
        // send a command to set a breakpoint at this time
        int error = ngSpice_Command(break_cmd);
        free(break_cmd);

        if (error) {
            printf("error when sending command: '%s' - check stderr\n", break_cmd);
            exit(1);
        }

        // store the rest of the input/output values on
        // the current row in 'input_output_values'
        while ((cmp_file_pos + 1) < cmp_file_len && cmp_file[++cmp_file_pos] != '\n') {
            if (cmp_file[cmp_file_pos] == '?'
                || cmp_file[cmp_file_pos] == '0'
                || cmp_file[cmp_file_pos] == '1') {
                input_output_values[i] = cmp_file[cmp_file_pos];
                input_output_len = ++i;
            }
        }
    }

    // TODO: realloc for good measure

    // run until the first breakpoint is hit
    int error = ngSpice_Command("run");
    if (error) {
        puts("error when sending command: 'run' - check stderr");
        exit(1);
    }

    int i = 0;
    while (i < input_output_len) {
        // loop over input values and set the corresponding input voltages
        for (int j = 0; spice_input_labels[j]; j++, i++) {
            char input_voltage = input_output_values[i] == '1' ? '5' : '0';
            send_ngspice_alter_cmd(spice_input_labels[j], input_voltage);
        }

        error = ngSpice_Command("resume");
        if (error) {
            puts("error when sending command: 'resume' - check stderr");
            exit(1);
        }

        // loop over output values and test the corresponding output voltages
        for (int j = 0; spice_output_labels[j]; j++, i++) {
            float output_voltage = get_ngspice_vector_voltage(spice_output_labels[j]);
            printf("%s voltage: %fV\n", spice_output_labels[j], output_voltage);
            assert_correct_voltage(output_voltage, input_output_values[i]);
        }
    }

    puts("");
    free(input_output_values);
    munmap(cmp_file, cmp_file_len);
}

int
main(void)
{
    // initialize ngspice
    ngSpice_Init(ngspice_output_callback, NULL, ngspice_exit_callback,
                 NULL, NULL, NULL, NULL);

    test_combinational("not/test.sp",
         "not/Not.cmp",
         (const char *[]) { "vin", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("nand/test.sp",
         "nand/Nand.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("nor/test.sp",
         "nor/Nor.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("and/test.sp",
         "and/And.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("or/test.sp",
         "or/Or.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("xor/test.sp",
         "xor/Xor.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("mux/test.sp",
         "mux/Mux.cmp",
         (const char *[]) { "va", "vb", "vsel", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("dmux/test.sp",
         "dmux/DMux.cmp",
         (const char *[]) { "vin", "vsel", NULL },
         (const char *[]) { "na", "nb", NULL });

    test_combinational("4waymux/test.sp",
         "4waymux/4WayMux.cmp",
         (const char *[]) { "va", "vb", "vc", "vd",
                            "vsel0", "vsel1", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("halfadder/test.sp",
         "halfadder/HalfAdder.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nsum", "ncarry", NULL });

    test_combinational("fulladder/test.sp",
         "fulladder/FullAdder.cmp",
         (const char *[]) { "va", "vb", "vc", NULL },
         (const char *[]) { "nsum", "ncarry", NULL });

    test_combinational("8bitadder/test.sp",
         "8bitadder/Add8.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4",
                            "va3", "va2", "va1", "va0",
                            "vb7", "vb6", "vb5", "vb4",
                            "vb3", "vb2", "vb1", "vb0", NULL },
         (const char *[]) { "nsum7", "nsum6", "nsum5",
                            "nsum4", "nsum3", "nsum2",
                            "nsum1", "nsum0", "ncarry", NULL });

    test_combinational("8bitand/test.sp",
         "8bitand/And8.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4",
                            "va3", "va2", "va1", "va0",
                            "vb7", "vb6", "vb5", "vb4",
                            "vb3", "vb2", "vb1", "vb0", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("8bitxor/test.sp",
         "8bitxor/Xor8.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4",
                            "va3", "va2", "va1", "va0",
                            "vb7", "vb6", "vb5", "vb4",
                            "vb3", "vb2", "vb1", "vb0", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("8bitmux/test.sp",
         "8bitmux/Mux8.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4", "va3",
                            "va2", "va1", "va0", "vb7", "vb6",
                            "vb5", "vb4", "vb3", "vb2", "vb1",
                            "vb0", "vsel", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("8bitmux/test.sp",
         "8bitmux/Mux8.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4", "va3",
                            "va2", "va1", "va0", "vb7", "vb6",
                            "vb5", "vb4", "vb3", "vb2", "vb1",
                            "vb0", "vsel", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("8wayor/test.sp",
         "8wayor/Or8Way.cmp",
         (const char *[]) { "vin7", "vin6", "vin5",
                            "vin4", "vin3", "vin2",
                            "vin1", "vin0", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("8waynor/test.sp",
         "8waynor/Nor8Way.cmp",
         (const char *[]) { "vin7", "vin6", "vin5",
                            "vin4", "vin3", "vin2",
                            "vin1", "vin0", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("alu/test.sp",
         "alu/ALU.cmp",
         (const char *[]) { "vx7", "vx6", "vx5", "vx4", "vx3",
                            "vx2", "vx1", "vx0", "vy7", "vy6",
                            "vy5", "vy4", "vy3", "vy2", "vy1",
                            "vy0", "vzx", "vnx", "vzy", "vny",
                            "vf", "vnout", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            // NOTE: 'nout7' (the 8th bit of the output)
                            // is used as the ALU negative flag
                            "nout1", "nout0", "nzr", "nout7", NULL });

    test_sequential("srlatch/test.sp",
         "srlatch/SRLatch.cmp",
         (const char *[]) { "vs", "vr", NULL },
         (const char *[]) { "nq", NULL });

    test_sequential("dlatch/test.sp",
         "dlatch/DLatch.cmp",
         (const char *[]) { "vd", "ve", NULL },
         (const char *[]) { "nq", NULL });

    return 0;
}
