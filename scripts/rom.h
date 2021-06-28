
#ifndef ROM_H
#define ROM_H

#include "instruction.h"

// code to run on the cpu. computes the gcd of 12 and 36 using euclid's
// algorithm. see 'instruction.h' for the opcode macros used
static const unsigned char ROM[16] = {
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

#endif
