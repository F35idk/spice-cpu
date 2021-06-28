
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <string.h>

// opcodes for every instruction

#define OPC_FETCH_1   (unsigned char)  (0b0000 << 4)
#define OPC_FETCH_2   (unsigned char)  (0b0001 << 4)
#define STRAM_X(addr) (unsigned char) ((0b0010 << 4) | addr)
#define LDRAM_X(addr) (unsigned char) ((0b0011 << 4) | addr)
#define STRAM_Y(addr) (unsigned char) ((0b0100 << 4) | addr)
#define LDRAM_Y(addr) (unsigned char) ((0b0101 << 4) | addr)
#define LDROM_X(addr) (unsigned char) ((0b0110 << 4) | addr)
#define LDROM_Y(addr) (unsigned char) ((0b0111 << 4) | addr)
#define ADC           (unsigned char)  (0b1000 << 4)
#define SUB_X_Y       (unsigned char)  (0b1001 << 4)
#define AND           (unsigned char)  (0b1010 << 4)
#define SUB_Y_X       (unsigned char)  (0b1011 << 4)
#define CMP           (unsigned char)  (0b1100 << 4)
#define BEQ(addr)     (unsigned char) ((0b1101 << 4) | addr)
#define BLT(addr)     (unsigned char) ((0b1110 << 4) | addr)
#define JMP(addr)     (unsigned char) ((0b1111 << 4) | addr)

static char *
instruction_to_string(unsigned char instruction)
{
    static char output[13];

    switch (instruction & 0xf0) {
        case 0b00000000:
        case 0b00010000:
            strcpy(output, "OPCODE FETCH");
            break;
        case 0b00100000:
            sprintf(output, "STRAM X, %#x", instruction & 0xf);
            break;
        case 0b00110000:
            sprintf(output, "LDRAM X, %#x", instruction & 0xf);
            break;
        case 0b01000000:
            sprintf(output, "STRAM Y, %#x", instruction & 0xf);
            break;
        case 0b01010000:
            sprintf(output, "LDRAM Y, %#x", instruction & 0xf);
            break;
        case 0b01100000:
            sprintf(output, "LDROM X, %#x", instruction & 0xf);
            break;
        case 0b01110000:
            sprintf(output, "LDROM Y, %#x", instruction & 0xf);
            break;
        case 0b10000000:
            strcpy(output, "ADC");
            break;
        case 0b10010000:
            strcpy(output, "SUB X, Y");
            break;
        case 0b10100000:
            strcpy(output, "AND");
            break;
        case 0b10110000:
            strcpy(output, "SUB Y, X");
            break;
        case 0b11000000:
            strcpy(output, "CMP");
            break;
        case 0b11010000:
            sprintf(output, "BEQ %#x", instruction & 0xf);
            break;
        case 0b11100000:
            sprintf(output, "BLT %#x", instruction & 0xf);
            break;
        case 0b11110000:
            sprintf(output, "JMP %#x", instruction & 0xf);
            break;
        default:
            sprintf(output, "invalid: %#x", instruction & 0xf0);
            break;
    }

    return output;
}

#endif
