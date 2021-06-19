
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include "util.h"
#include "cpu_state.h"
#include "emulate.h"
#include "simulate.h"
#include "instruction.h"
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
    // code to compute the gcd of 36 and 12
    const unsigned char rom_1[16] = {
        LDROM_X(0xe),  // load 12 into x
        LDROM_Y(0xf),  // load 36 into y
        [2] = CMP,
        BEQ(2),        // branch back to rom[2] if x and y are equal
        BLT(7),        // go to rom[7] if x < y
        SUB_X_Y,       // x = x - y
        JMP(2),        // go to rom[2]
        [7] = SUB_Y_X, // y = y - x
        JMP(2),        // go to rom[2]
        [0xe] = 12,
        [0xf] = 36,
    };

    // AND, STRAM and LDRAM testing
    const unsigned char rom_2[16] = {
        LDROM_X(0xe),
        LDROM_Y(0xf),
        AND,
        BEQ(0),
        STRAM_X(0),
        STRAM_Y(1),
        LDRAM_X(1),
        LDRAM_Y(0),
        [0xe] = 0xff,
        [0xf] = 0xcd,
    };

    test_cpu(&rom_1, 33);
    test_cpu(&rom_2, 24);

    return 0;
}
