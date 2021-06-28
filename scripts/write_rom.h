
#ifndef WRITE_ROM_H
#define WRITE_ROM_H

// writes the memory in 'rom' into a rom netlist (see rom/rom.inc)
// NOTE: this assumes the rom netlist has already been loaded into ngspice
void write_rom(
    const unsigned char (*rom)[16],
    const char *rom_instance_name
);

// writes microcode into the decode ROMs in the control unit given by
// 'control_unit_instance_name'
void init_decode_rom(const char *control_unit_instance_name);

#endif
