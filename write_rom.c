
#include <string.h>
#include <stdbool.h>
#include <ngspice/sharedspice.h>
#include <stdlib.h>
#include "write_rom.h"
#include "util.h"
#include "instruction.h"

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

void
write_rom(
    const unsigned char (*rom)[16],
    const char *rom_instance_name
)
{
    int byte_circuit_name_len = sizeof("v.") - 1 + strlen(rom_instance_name) + sizeof(".xxbyte__") - 1
        + sizeof(".v_");
    char *byte_circuit_name = calloc(1, byte_circuit_name_len);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            snprintf(byte_circuit_name, byte_circuit_name_len,
                     "v.%s.xxbyte%i.v%i", rom_instance_name, i, j);

            if ((*rom)[i] & (1 << j))
                send_ngspice_alter_cmd(byte_circuit_name, '0'); // data is inverted before being output from ROM
            else
                send_ngspice_alter_cmd(byte_circuit_name, '5');
        }
    }
}

static void
write_decode_rom(
    const ControlSignal (*rom)[16],
    const char *control_unit_instance_name
)
{
    unsigned char decode_roms[3][16];
    // mask to xor the control signals with. ensures that signals
    // that are stored as active-low in the decode roms are inverted
    int control_signal_invert_mask = 0b1010101011111101111100;

    for (int i = 0; i < 16; i++) {
        ControlSignal signal = (*rom)[i];
        signal ^= control_signal_invert_mask;
        decode_roms[0][i] = (char) signal;
        decode_roms[1][i] = (char) (signal >> 8);
        decode_roms[2][i] = (char) (signal >> 16);
    }

    int rom_instance_name_len = strlen(control_unit_instance_name) + sizeof(".xxrom_");
    char *rom_instance_name = calloc(1, rom_instance_name_len);

    for (int i = 0; i < 3; i++) {
        // the 3 decode roms in the CU are named 'xxrom0',
        // 'xxrom1' and 'xxrom2' in the netlist
        snprintf(rom_instance_name, rom_instance_name_len,
                 "%s.xxrom%i", control_unit_instance_name, i);
        write_rom(&decode_roms[i], rom_instance_name);
    }

    free(rom_instance_name);
}

void
init_decode_rom(const char *control_unit_instance_name)
{
    const ControlSignal rom[16] = {
        [OPC_FETCH_1 >> 4] = PC_OUT | MAR_IN, // opcode fetch (cycle 1)
        [OPC_FETCH_2 >> 4] = MAR_IN | ROM_OUT | IR_IN | COUNT_ENABLE, // opcode fetch (cycle 2)
        [STRAM_X(0)  >> 4] = X_OUT | RAM_IN, // STRAM X, $ADDR
        [LDRAM_X(0)  >> 4] = RAM_OUT | X_IN, // LDRAM X, $ADDR
        [STRAM_Y(0)  >> 4] = Y_OUT | RAM_IN, // STRAM Y, $ADDR
        [LDRAM_Y(0)  >> 4] = RAM_OUT | Y_IN, // LDRAM Y, $ADDR
        [LDROM_X(0)  >> 4] = ROM_OUT | X_IN, // LDROM X, $ADDR
        [LDROM_Y(0)  >> 4] = ROM_OUT | Y_IN, // LDROM Y, $ADDR
        [ADC         >> 4] = ADD | CARRY | ALU_OUT | FLAGS_IN | X_IN, // ADC
        [SUB_X_Y     >> 4] = ADD | NOT_X | NOT_OUT | ALU_OUT | FLAGS_IN | X_IN, // SUB X, Y
        [AND         >> 4] = ALU_OUT | FLAGS_IN | X_IN, // AND
        [SUB_Y_X     >> 4] = ADD | NOT_Y | NOT_OUT | ALU_OUT | FLAGS_IN | Y_IN, // SUB Y, X
        [CMP         >> 4] = ADD | NOT_X | NOT_OUT | FLAGS_IN, // CMP
        [BEQ(0)      >> 4] = IR_OUT | BRANCH_ZR, // BEQ $ADDR
        [BLT(0)      >> 4] = IR_OUT | BRANCH_CARRY, // BLT $ADDR
        [JMP(0)      >> 4] = IR_OUT | PC_IN, // JMP $ADDR
    };

    write_decode_rom(&rom, control_unit_instance_name);
}
