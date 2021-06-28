
#include <stdio.h>
#include <stdbool.h>
#include <ngspice/sharedspice.h>
#include "util.h"
#include "cpu_state.h"
#include "emulate.h"
#include "simulate.h"
#include "rom.h"

int
main(int argc, char *argv[])
{
    int n_cycles = 0;
    char *output_raw_file = NULL;
    bool emulate = false;

    if (argc < 2) {
        fputs("error: too few arguments\n", stderr);
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        if (!strcmp("-n", argv[i]) || !strcmp("--cycles", argv[i])) {
            i++;
            n_cycles = strtol(argv[i], NULL, 10);
            if (!n_cycles) {
                fputs("error: invalid cycle count", stderr);
                exit(1);
            }
        }
        else if (!strcmp("-o", argv[i]) || !strcmp("--output", argv[i])) {
            i++;
            output_raw_file = argv[i];
        }
        else if (!strcmp("-e", argv[i]) || !strcmp("--emulate", argv[i])) {
            emulate = true;
        }
        else {
            fprintf(stderr, "error: invalid argument: %s\n", argv[i]);
            exit(1);
        }
    }

    if (emulate)
        emulate_cpu(&ROM, n_cycles, true);
    else
        simulate_cpu(&ROM, n_cycles, output_raw_file, true);

    return 0;
}
