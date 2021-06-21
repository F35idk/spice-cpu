
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include "util.h"
#include "instruction.h"
#include "cpu_state.h"
#include "emulate.h"

// instruction-accurate emulation for testing the simulation against

CpuState *
emulate_cpu(const unsigned char (*rom)[16], int n_cycles)
{
    assert(n_cycles % 3 == 0);
    int n_instructions = n_cycles / 3;
    CpuState *cpu_states = calloc(1, n_instructions * sizeof(CpuState));
    CpuState cpu = {0};
    char ram[16] = {0};

    for (int i = 0; i < n_instructions; i++) {
        cpu.ir = (*rom)[cpu.pc];
        cpu.current_cycle = 3 + i * 3;
        cpu.mar = cpu.ir & 0xf;
        cpu.pc += 1;

        #ifdef DEBUG
        printf("%s\n", instruction_to_string(cpu.ir));
        #endif

        switch (cpu.ir & 0xf0) {
            case 0b00100000: {
                ram[cpu.ir & 0xf] = cpu.x;
                break;
            }
            case 0b00110000: {
                cpu.x = ram[cpu.ir & 0xf];
                break;
            }
            case 0b01000000: {
                ram[cpu.ir & 0xf] = cpu.y;
                break;
            }
            case 0b01010000: {
                cpu.y = ram[cpu.ir & 0xf];
                break;
            }
            case 0b01100000: {
                cpu.x = (*rom)[cpu.ir & 0xf];
                break;
            }
            case 0b01110000: {
                cpu.y = (*rom)[cpu.ir & 0xf];
                break;
            }
            case 0b10000000: {
                cpu.carry = __builtin_add_overflow((unsigned char) cpu.x, cpu.y, &cpu.x);
                cpu.zero = (cpu.x == 0);
                break;
            }
            case 0b10010000: {
                unsigned char res;
                cpu.carry = __builtin_add_overflow((unsigned char) ~cpu.x, cpu.y, &res);
                cpu.x = ~res;
                cpu.zero = (cpu.x == 0);
                break;
            }
            case 0b10100000: {
                cpu.x &= cpu.y;
                cpu.zero = (cpu.x == 0);
                unsigned char dummy;
                // set the carry flag as if an ADC was performed
                cpu.carry = __builtin_add_overflow((unsigned char) cpu.x, cpu.y, &dummy);
                break;
            }
            case 0b10110000: {
                unsigned char res;
                cpu.carry = __builtin_add_overflow((unsigned char) ~cpu.y, cpu.x, &res);
                cpu.y = ~res;
                cpu.zero = (cpu.y == 0);
                break;
            }
            case 0b11000000: {
                unsigned char res;
                cpu.carry = __builtin_add_overflow((unsigned char) ~cpu.x, cpu.y, &res);
                res = ~res;
                cpu.zero = (res == 0);
                break;
            }
            case 0b11010000: {
                if (cpu.zero)
                    cpu.pc = cpu.ir & 0xf;
                break;
            }
            case 0b11100000: {
                if (cpu.carry)
                    cpu.pc = cpu.ir & 0xf;
                break;
            }
            case 0b11110000: {
                cpu.pc = cpu.ir & 0xf;
                break;
            }
            default: {
                printf("invalid opcode: 0x%x\n", cpu.ir & 0xf0);
                exit(1);
                break;
            }
        }

        cpu_states[i] = cpu;
    }

    cpu_states[n_instructions - 1].is_last = true;
    return cpu_states;
}
