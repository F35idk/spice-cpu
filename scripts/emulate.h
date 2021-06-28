
#ifndef EMULATE_H
#define EMULATE_H

#include "cpu_state.h"

// instruction-accurate emulation for testing the simulation against

CpuState *emulate_cpu(const unsigned char (*rom)[16], int n_cycles, bool print_state);

#endif
