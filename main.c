
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ngspice/sharedspice.h>
#include "util.h"
#include "cpu_state.h"
#include "emulate.h"
#include "simulate.h"
#include "rom.h"

int
main(void)
{
    simulate_cpu(34);
    return 0;
}
