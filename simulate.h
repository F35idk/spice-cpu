#ifndef SIMULATE_H
#define SIMULATE_H

#include "cpu_state.h"

// simulates the cpu in ngspice for 'n_cycles'
CpuState *simulate_cpu(const unsigned char (*rom)[16], int n_cycles);

#endif
