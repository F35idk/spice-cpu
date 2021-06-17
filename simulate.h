#ifndef SIMULATE_H
#define SIMULATE_H

#include "cpu_state.h"

// simulates the cpu in ngspice for 'n_cycles'
CpuState *simulate_cpu(int n_cycles);

#endif
