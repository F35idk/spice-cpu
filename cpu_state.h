
#ifndef CPU_STATE_H
#define CPU_STATE_H

#include <stdio.h>
#include <stdbool.h>
#include "instruction.h"

typedef struct {
    // 8-bit x-register
    unsigned char x;
    // 8-bit y-register
    unsigned char y;
    // 4-bit program counter
    unsigned char pc;
    // 4-bit memory address register
    unsigned char mar;
    // 8-bit instruction register
    unsigned char ir;
    // zero and carry flags
    bool zero;
    bool carry;
    // whether this CpuState is last in the CpuState array
    bool is_last;
    int current_cycle;
} CpuState;

static void
cpu_state_print(CpuState *self)
{
    printf("cycle: %i\nx: %x\ny: %x\npc: %x\nmar: %x\nir: %x\nzr: %x\ncarry: %x\n",
           self->current_cycle, self->x, self->y, self->pc, self->mar, self->ir,
           self->zero, self->carry);
}

static void
cpu_state_print_column_header(void)
{
    puts("| cycle |  instruction  |  pc  |   x   |   y   |  mar  |  ir  | zero | carry |");
}

static void
cpu_state_print_columns(CpuState *self)
{

    printf("|  %4i | %13s |  0x%x |  0x%02x |  0x%02x |  0x%x  | 0x%02x |   %i  |   %i   |\n",
           self->current_cycle, instruction_to_string(self->ir), self->pc & 0xf, self->x,
           self->y, self->mar & 0xf, self->ir, self->zero, self->carry);
}

#endif
