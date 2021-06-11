
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include "util.h"

// cpu constants
static const char CPU_CYCLE_LEN = 4;
// the delay before powering on in microseconds
static const char POWER_ON_DELAY = 2;
// the length (in microseconds) of the power-on reset pulse
static const char POWER_ON_RESET_PULSE_LEN = 7;

// simulation constants
static const char NGSPICE_TRAN_STEP_NS = 30;
static const char *NGSPICE_RSHUNT = "option rshunt=1e9";
static const char *NGSPICE_ITL1 = "option itl1=300";

// TODO: stop-condition function
// TODO: make emulator, dump state, compare with simulated state?? allows easily testing programs

static void
simulate_cpu(int n_cycles)
{
    // initialize ngspice
    ngSpice_Init(ngspice_output_callback, NULL, ngspice_exit_callback,
                 NULL, NULL, NULL, NULL);

    // send command to open the cpu netlist
    send_ngspice_cmd("source cpu/test.sp");

    char *save_cmd = "save" " v(nx7)"  " v(nx6)"  " v(nx5)"
                     " v(nx4)"  " v(nx3)"  " v(nx2)"
                     " v(nx1)"  " v(nx0)"  " v(nd7)"
                     " v(nd6)"  " v(nd5)"  " v(nd4)"
                     " v(nd3)"  " v(nd2)"  " v(nd1)"
                     " v(nd0)"  " v(nmar3)"  " v(nmar2)"
                     " v(nmar1)"  " v(nmar0)"  " v(nir7)"
                     " v(nir6)"  " v(nir5)"  " v(nir4)"
                     " v(nir3)"  " v(nir2)"  " v(nir1)"
                     " v(nir0)"  " v(npc3)"  " v(npc2)"
                     " v(npc1)"  " v(npc0)" " v(clk)"
                     " v(reset)" " v(vdd)" " v(~alu_out)"
                     " v(~carry)" " v(add)" " v(branch_zr)"
                     " v(count_enable)" " v(flags_in)"
                     " v(ir_in)" " v(~ir_out)"
                     " v(mar_in)" " v(not_out)"
                     " v(not_x)" " v(not_y)" " v(pc_in)"
                     " v(pc_out)" " v(~ram_in)"
                     " v(ram_out)" " v(~rom_out)"
                     " v(x_in)" " v(~x_out)"
                     " v(y_in)" " v(~y_out)"
                     " v(branch_carry)";

    // send command to only save voltages of the specified nodes
    send_ngspice_cmd(save_cmd);

    // send option commands
    send_ngspice_cmd(NGSPICE_RSHUNT);
    send_ngspice_cmd(NGSPICE_ITL1);

    // calculate time to run the cpu in microseconds
    int time = POWER_ON_DELAY
        + POWER_ON_RESET_PULSE_LEN
        + n_cycles * CPU_CYCLE_LEN;

    // set breakpoint at every cycle
    for (int i = POWER_ON_DELAY + POWER_ON_RESET_PULSE_LEN; i < time; i += CPU_CYCLE_LEN) {
        set_ngspice_breakpoint_in_us(i);
        printf("%i\n", i);
    }

    // set breakpoint for powering on
    set_ngspice_breakpoint_in_us(POWER_ON_DELAY);

    // send command to start simulation
    {
        #define TRAN_CMD_LEN sizeof("tran ns u") - 1 + INT_MAX_DIGITS * 2 + 1
        char tran_cmd[TRAN_CMD_LEN];

        snprintf(tran_cmd, TRAN_CMD_LEN, "tran %ins %iu",
                 NGSPICE_TRAN_STEP_NS, time);

        puts(tran_cmd);

        // tell ngspice to begin transient analysis
        send_ngspice_cmd(tran_cmd);
        #undef TRAN_CMD_LEN
    }

    // first breakpoint - set 'vsource' to 5V (power-on)
    send_ngspice_alter_cmd("vsource", '5');
    send_ngspice_cmd("resume");

    for (int i = 0; i < n_cycles; i++) {
        unsigned char x_register = 0;
        unsigned char y_register = 0;
        unsigned char program_counter = 0;
        unsigned char memory_address_register = 0;
        unsigned char instruction_register = 0;
        unsigned char data_bus = 0;

        printf("~rom_out: %f\n", get_ngspice_vector_voltage("~rom_out"));
        printf("x_in: %f\n", get_ngspice_vector_voltage("x_in"));
        printf("pc_in: %f\n", get_ngspice_vector_voltage("pc_in"));
        printf("pc_out: %f\n", get_ngspice_vector_voltage("pc_out"));

        for (int j = 0; j < 8; j++) {
            if (get_ngspice_vector_voltage_fmt("nx%i", j) > 4.0)
                x_register |= (1 << j);

            if (get_ngspice_vector_voltage_fmt("nd%i", j) > 4.0)
                data_bus |= (1 << j);

            if (get_ngspice_vector_voltage_fmt("nir%i", j) > 4.0)
                instruction_register |= (1 << j);
        }

        for (int j = 0; j < 4; j++) {
            if (get_ngspice_vector_voltage_fmt("npc%i", j) > 4.0)
                program_counter |= (1 << j);

            if (get_ngspice_vector_voltage_fmt("nmar%i", j) > 4.0)
                memory_address_register |= (1 << j);
        }

        printf("x: %x\ny: ??\npc: %x\nmar: %x\nir: %x\nd: %x\n",
               x_register, program_counter, memory_address_register,
               instruction_register, data_bus);

        send_ngspice_cmd("resume");
    }

    char *write_cmd = "write out.raw";
    send_ngspice_cmd(write_cmd);
}

int
main(void)
{
    // TODO: parse command-line input, run simulation

    return 0;
}
