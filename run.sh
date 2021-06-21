#!/usr/bin/env bash

# recompile to update rom (in rom.h)
gcc main.c emulate.c simulate.c write_rom.c util.c -lngspice > /dev/null 2>&1
./a.out "$@"
rm a.out
