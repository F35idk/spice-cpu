
#include <stdio.h>
#include "util.h"

typedef enum {
    ALU_OUT      = 0x1,
    CARRY        = 0x2,
    ADD          = 0x4,
    BRANCH_ZR    = 0x8,
    COUNT_ENABLE = 0x10,
    FLAGS_IN     = 0x20,
    IR_IN        = 0x40,
    IR_OUT       = 0x80,
    MAR_IN       = 0x100,
    NOT_OUT      = 0x200,
    NOT_X        = 0x400,
    NOT_Y        = 0x800,
    PC_IN        = 0x1000,
    PC_OUT       = 0x2000,
    RAM_IN       = 0x4000,
    RAM_OUT      = 0x8000,
    ROM_OUT      = 0x10000,
    X_IN         = 0x20000,
    X_OUT        = 0x40000,
    Y_IN         = 0x80000,
    Y_OUT        = 0x100000,
    BRANCH_CARRY = 0x200000,
} ControlSignal;

static void
write_decode_rom(const ControlSignal (*rom)[16])
{
    char decode_rom_1[16];
    char decode_rom_2[16];
    char decode_rom_3[16];
    // mask to xor the control signals with. ensures that signals
    // that are stored as active-low in the decode roms are inverted
    int control_signal_invert_mask = 0b1010101011111101111100;

    for (int i = 0; i < 16; i++) {
        ControlSignal signal = (*rom)[i];
        signal ^= control_signal_invert_mask;
        decode_rom_1[i] = (char) signal;
        decode_rom_2[i] = (char) (signal >> 8);
        decode_rom_3[i] = (char) (signal >> 16);
    }

    write_rom(&decode_rom_1, "control_unit/decode_rom_1.inc");
    write_rom(&decode_rom_2, "control_unit/decode_rom_2.inc");
    write_rom(&decode_rom_3, "control_unit/decode_rom_3.inc");
}

int
main(void)
{
    const ControlSignal rom[16] = {
        [0b0000] = PC_OUT | MAR_IN, // opcode fetch (cycle 1)
        [0b0001] = MAR_IN | ROM_OUT | IR_IN | COUNT_ENABLE, // opcode fetch (cycle 2)
        [0b0010] = X_OUT | RAM_IN, // STRAM X, $ADDR
        [0b0011] = RAM_OUT | X_IN, // LDRAM X, $ADDR
        [0b0100] = Y_OUT | RAM_IN, // STRAM Y, $ADDR
        [0b0101] = RAM_OUT | Y_IN, // LDRAM Y, $ADDR
        [0b0110] = ROM_OUT | X_IN, // LDROM X, $ADDR
        [0b0111] = ROM_OUT | Y_IN, // LDROM Y, $ADDR
        [0b1000] = ADD | CARRY | ALU_OUT | FLAGS_IN | X_IN, // ADC
        [0b1001] = ADD | NOT_X | NOT_OUT | ALU_OUT | FLAGS_IN | X_IN, // SUB
        [0b1010] = ALU_OUT | FLAGS_IN | X_IN, // AND
        [0b1011] = NOT_X | NOT_Y | NOT_OUT | ALU_OUT | FLAGS_IN | X_IN, // OR
        [0b1100] = ADD | NOT_X | NOT_OUT | FLAGS_IN, // CMP
        [0b1101] = IR_OUT | BRANCH_ZR, // BEQ
        [0b1110] = IR_OUT | BRANCH_CARRY, // BGE
        [0b1111] = IR_OUT | PC_IN, // JMP
    };

    write_decode_rom(&rom);

    return 0;
}
