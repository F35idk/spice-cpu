#!/usr/bin/env bash

# recompile to update rom (in rom.h)
gcc scripts/main.c scripts/emulate.c scripts/simulate.c scripts/write_rom.c scripts/util.c -lngspice > /dev/null 2>&1
./a.out "$@"
rm a.out
