
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include "util.h"
#include "cpu_state.h"
#include "emulate.h"
#include "simulate.h"
#include "rom.h"

static void
test_cpu(const unsigned char (*rom)[16], int n_cycles)
{
    CpuState *emulated_cpu_states = emulate_cpu(rom, n_cycles);
    CpuState *simulated_cpu_states = simulate_cpu(rom, n_cycles);

    for (int i = 0; i < n_cycles / 3; i += 1) {
        puts("emulated CPU state:");
        cpu_state_print(&emulated_cpu_states[i]);

        puts("simulated CPU state:");
        cpu_state_print(&simulated_cpu_states[(i + 1) * 3]);
        fflush(stdout);

        assert(!memcmp(&emulated_cpu_states[i],
                       &simulated_cpu_states[(i + 1) * 3], sizeof(CpuState)));
    }
}

int
main(void)
{
    test_cpu(&ROM, 33);
    return 0;
}
