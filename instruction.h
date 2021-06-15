
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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

#endif
