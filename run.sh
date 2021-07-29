#!/usr/bin/env bash

# recompile to update rom (in rom.h)
gcc_output=$(gcc scripts/main.c scripts/emulate.c scripts/simulate.c scripts/write_rom.c scripts/util.c -lngspice 2>&1)
if [ $? -eq 0 ]
then
    # compilation succeeded
    ./a.out "$@"
    rm a.out
else
    # compilation failed, print errors
    echo $gcc_output
    exit
fi
