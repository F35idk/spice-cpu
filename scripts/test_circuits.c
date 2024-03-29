
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
// tell the functions in 'util.h' to print debug info
#define DEBUG
#include "util.h"
#include "write_rom.h"

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
    char *source_cmd = calloc(1, cmd_len);
    snprintf(source_cmd, cmd_len, "source %s", netlist_path);
    // send command to open netlist file
    send_ngspice_cmd(source_cmd);
    free(source_cmd);

    // delete all previous breakpoints
    send_ngspice_cmd("delete all");
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
        send_ngspice_cmd("run");

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
    // function for setting any state in the netlist before
    // testing (such as initializing ROM)
    void (*init_func)(void),
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

    if (init_func)
        init_func();

    cmp_file_pos = 0;

    while ((cmp_file_pos + 1) < cmp_file_len && cmp_file[++cmp_file_pos] != '\n')
        continue;

    input_output_len = cmp_file_len; // more bytes than needed
    input_output_values = calloc(1, cmp_file_len - cmp_file_pos);

    // set breakpoints at the right times and gather up
    // all of the input/output values in the cmp file
    for (int i = 0; cmp_file_pos < cmp_file_len; cmp_file_pos++) {
        // skip to the first character that is a number (ascii 0x30-0x39)
        while (cmp_file[cmp_file_pos] < 0x30 || cmp_file[cmp_file_pos] > 0x39)
            cmp_file_pos++;

        char *new_cmp_file_pos = NULL;
        double time = (strtod(&cmp_file[cmp_file_pos], &new_cmp_file_pos) + 0.1);
        int cmd_len = 30;
        char *break_cmd = calloc(1, cmd_len);
        snprintf(break_cmd, cmd_len, "stop when time = %fus", time);
        // send a command to set a breakpoint at this time
        send_ngspice_cmd(break_cmd);
        free(break_cmd);

        cmp_file_pos = (int) (new_cmp_file_pos - &cmp_file[0]);

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
    send_ngspice_cmd("run");

    for (int i = 0; i < input_output_len;) {
        // loop over input values and set the corresponding input voltages
        for (int j = 0; spice_input_labels[j]; j++, i++) {
            char input_voltage = input_output_values[i] == '1' ? '5' : '0';
            send_ngspice_alter_cmd(spice_input_labels[j], input_voltage);
        }

        send_ngspice_cmd("resume");

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

static void
init_control_unit_test(void)
{
    init_decode_rom("xxcu");
}

int
main(void)
{
    // initialize ngspice
    ngSpice_Init(ngspice_output_callback, NULL, ngspice_exit_callback,
                 NULL, NULL, NULL, NULL);

    test_combinational("circuits/ngspice/not/test.sp",
         "circuits/ngspice/not/not.cmp",
         (const char *[]) { "vin", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/nand/test.sp",
         "circuits/ngspice/nand/nand.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/nor/test.sp",
         "circuits/ngspice/nor/nor.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/and/test.sp",
         "circuits/ngspice/and/and.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/or/test.sp",
         "circuits/ngspice/or/or.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/xor/test.sp",
         "circuits/ngspice/xor/xor.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/mux/test.sp",
         "circuits/ngspice/mux/mux.cmp",
         (const char *[]) { "va", "vb", "vsel", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/dmux/test.sp",
         "circuits/ngspice/dmux/dmux.cmp",
         (const char *[]) { "vin", "vsel", NULL },
         (const char *[]) { "na", "nb", NULL });

    test_combinational("circuits/ngspice/4_way_mux/test.sp",
         "circuits/ngspice/4_way_mux/4_way_mux.cmp",
         (const char *[]) { "va", "vb", "vc", "vd",
                            "vsel0", "vsel1", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/half_adder/test.sp",
         "circuits/ngspice/half_adder/half_adder.cmp",
         (const char *[]) { "va", "vb", NULL },
         (const char *[]) { "nsum", "ncarry", NULL });

    test_combinational("circuits/ngspice/full_adder/test.sp",
         "circuits/ngspice/full_adder/full_adder.cmp",
         (const char *[]) { "va", "vb", "vc", NULL },
         (const char *[]) { "nsum", "ncarry", NULL });

    test_combinational("circuits/ngspice/8_bit_adder/test.sp",
         "circuits/ngspice/8_bit_adder/8_bit_adder.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4",
                            "va3", "va2", "va1", "va0",
                            "vb7", "vb6", "vb5", "vb4",
                            "vb3", "vb2", "vb1", "vb0", NULL },
         (const char *[]) { "nsum7", "nsum6", "nsum5",
                            "nsum4", "nsum3", "nsum2",
                            "nsum1", "nsum0", "ncarry", NULL });

    test_combinational("circuits/ngspice/8_bit_and/test.sp",
         "circuits/ngspice/8_bit_and/8_bit_and.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4",
                            "va3", "va2", "va1", "va0",
                            "vb7", "vb6", "vb5", "vb4",
                            "vb3", "vb2", "vb1", "vb0", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("circuits/ngspice/8_bit_xor/test.sp",
         "circuits/ngspice/8_bit_xor/8_bit_xor.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4",
                            "va3", "va2", "va1", "va0",
                            "vb7", "vb6", "vb5", "vb4",
                            "vb3", "vb2", "vb1", "vb0", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("circuits/ngspice/8_bit_mux/test.sp",
         "circuits/ngspice/8_bit_mux/8_bit_mux.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4", "va3",
                            "va2", "va1", "va0", "vb7", "vb6",
                            "vb5", "vb4", "vb3", "vb2", "vb1",
                            "vb0", "vsel", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("circuits/ngspice/8_bit_mux/test.sp",
         "circuits/ngspice/8_bit_mux/8_bit_mux.cmp",
         (const char *[]) { "va7", "va6", "va5", "va4", "va3",
                            "va2", "va1", "va0", "vb7", "vb6",
                            "vb5", "vb4", "vb3", "vb2", "vb1",
                            "vb0", "vsel", NULL },
         (const char *[]) { "nout7", "nout6", "nout5",
                            "nout4", "nout3", "nout2",
                            "nout1", "nout0", NULL });

    test_combinational("circuits/ngspice/8_way_or/test.sp",
         "circuits/ngspice/8_way_or/8_way_or.cmp",
         (const char *[]) { "vin7", "vin6", "vin5",
                            "vin4", "vin3", "vin2",
                            "vin1", "vin0", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/8_way_nor/test.sp",
         "circuits/ngspice/8_way_nor/8_way_nor.cmp",
         (const char *[]) { "vin7", "vin6", "vin5",
                            "vin4", "vin3", "vin2",
                            "vin1", "vin0", NULL },
         (const char *[]) { "nout", NULL });

    test_combinational("circuits/ngspice/alu/test.sp",
         "circuits/ngspice/alu/alu.cmp",
         (const char *[]) { "vx7", "vx6", "vx5", "vx4", "vx3",
                            "vx2", "vx1", "vx0", "vy7", "vy6",
                            "vy5", "vy4", "vy3", "vy2", "vy1",
                            "vy0", "vnx", "vny", "vf", "vnout",
                            "v~oe", NULL },
         (const char *[]) { "nq7", "nq6", "nq5",
                            "nq4", "nq3", "nq2",
                            // NOTE: 'nq7' (the 8th bit of the output)
                            // is used as the ALU negative flag
                            "nq1", "nq0", "nzr", "nq7", "ncout", NULL });

    test_sequential(NULL, "circuits/ngspice/sr_latch/test.sp",
         "circuits/ngspice/sr_latch/sr_latch.cmp",
         (const char *[]) { "vs", "vr", NULL },
         (const char *[]) { "nq", NULL });

    test_sequential(NULL, "circuits/ngspice/d_latch/test.sp",
         "circuits/ngspice/d_latch/d_latch.cmp",
         (const char *[]) { "vd", "v~e", NULL },
         (const char *[]) { "nq", NULL });

    test_sequential(NULL, "circuits/ngspice/d_flip_flop/test.sp",
         "circuits/ngspice/d_flip_flop/d_flip_flop.cmp",
         (const char *[]) { "vd", "vclk", NULL },
         (const char *[]) { "nq", NULL });

    test_sequential(NULL, "circuits/ngspice/jk_flip_flop/test.sp",
         "circuits/ngspice/jk_flip_flop/jk_flip_flop.cmp",
         (const char *[]) { "vj", "vk", "vclk", NULL },
         (const char *[]) { "nq", NULL });

    test_sequential(NULL, "circuits/ngspice/8_bit_register/test.sp",
         "circuits/ngspice/8_bit_register/8_bit_register.cmp",
         (const char *[]) { "vd7", "vd6", "vd5",
                            "vd4", "vd3", "vd2",
                            "vd1", "vd0", "vclk",
                            "vie", "v~oe", NULL },
         (const char *[]) { "nq7", "nq6", "nq5",
                            "nq4", "nq3", "nq2",
                            "nq1", "nq0", "nd7",
                            "nd6", "nd5", "nd4",
                            "nd3", "nd2", "nd1",
                            "nd0",  NULL });

    test_combinational("circuits/ngspice/4_to_16_decoder/test.sp",
         "circuits/ngspice/4_to_16_decoder/4_to_16_decoder.cmp",
         (const char *[]) { "va", "vb", "vc",
                            "vd", NULL },
         (const char *[]) { "nd0", "nd1", "nd2",
                            "nd3", "nd4", "nd5",
                            "nd6", "nd7", "nd8",
                            "nd9", "nd10", "nd11",
                            "nd12", "nd13", "nd14",
                            "nd15", NULL });

    test_sequential(NULL, "circuits/ngspice/sram/test.sp", "circuits/ngspice/sram/sram.cmp",
         (const char *[]) { "va3", "va2", "va1",
                            "va0", "vd7", "vd6",
                            "vd5", "vd4", "vd3",
                            "vd2", "vd1", "vd0",
                            "v~we", "voe", NULL },
         (const char *[]) { "nd7", "nd6", "nd5",
                            "nd4", "nd3", "nd2",
                            "nd1", "nd0", NULL });

    test_sequential(NULL, "circuits/ngspice/program_counter/test.sp",
         "circuits/ngspice/program_counter/program_counter.cmp",
         (const char *[]) { "vd3", "vd2", "vd1",
                            "vd0", "voe", "vce",
                            "vie", "vrst", "vclk", NULL },
         (const char *[]) { "nd3", "nd2",
                            "nd1", "nd0", NULL });

    test_sequential(NULL, "circuits/ngspice/mod_3_counter/test.sp",
         "circuits/ngspice/mod_3_counter/mod_3_counter.cmp",
         (const char *[]) { "v~clk", "vrst", NULL },
         (const char *[]) { "nq1", "nq0", NULL });

    test_sequential(init_control_unit_test,
         "circuits/ngspice/control_unit/test.sp",
         "circuits/ngspice/control_unit/control_unit.cmp",
         (const char *[]) { "vclk", "vrst", "vi7",
                            "vi6", "vi5", "vi4", NULL },
         (const char *[]) { "n~alu_out", "n~carry",
                            "nadd", "nbranch_zr",
                            "ncount_enable", "nflags_in",
                            "nir_in", "n~ir_out", "nmar_in",
                            "nnot_out", "nnot_x", "nnot_y",
                            "npc_in", "npc_out", "n~ram_in",
                            "nram_out", "n~rom_out", "nx_in",
                            "n~x_out", "ny_in", "n~y_out",
                            "nbranch_carry", NULL });

    test_sequential(NULL, "circuits/ngspice/dt_flip_flop/test.sp",
         "circuits/ngspice/dt_flip_flop/dt_flip_flop.cmp",
         (const char *[]) { "vclk", "vd", "v~t", "v~ie", NULL },
         (const char *[]) { "nq", NULL });

    return 0;
}
