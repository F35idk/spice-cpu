* 16-byte rom subcircuit

.include ../transmission_gate/transmission_gate.inc
.include ../not/not.inc
.include ../buffer/buffer.inc
.include ../nand/nand.inc
.include ../1_to_4_not/1_to_4_not.inc
.include ../4_to_16_decoder/4_to_16_decoder.inc

* an 8-bit rom cell. each voltage source (v0-v7) represents an inverted bit
.subckt 8_bit_rom_cell ~e q0 q1 q2 q3 q4 q5 q6 q7 vdd vss
xx1 e0 n003 ~e0 q0 vdd vss transmission_gate
xx2 e0 n007 ~e0 q1 vdd vss transmission_gate
xx3 e0 n011 ~e0 q2 vdd vss transmission_gate
xx4 e0 n015 ~e0 q3 vdd vss transmission_gate
xx5 e1 n005 ~e1 q4 vdd vss transmission_gate
xx6 e1 n009 ~e1 q5 vdd vss transmission_gate
xx7 e1 n013 ~e1 q6 vdd vss transmission_gate
xx8 e1 n017 ~e1 q7 vdd vss transmission_gate
xx9 ~e n001 vss vdd not
xx12 n001 e0 vss vdd buffer
xx10 n001 ~e0 vss vdd not
xx11 n001 ~e1 vss vdd not
xx13 n001 e1 vss vdd buffer
v0 n002 vss 0
v1 n006 vss 0
v2 n010 vss 0
v3 n014 vss 0
v4 n004 vss 0
v5 n008 vss 0
v6 n012 vss 0
v7 n016 vss 0
xx14 n002 n003 vss vdd not
xx15 n006 n007 vss vdd not
xx16 n010 n011 vss vdd not
xx17 n014 n015 vss vdd not
xx18 n004 n005 vss vdd not
xx19 n008 n009 vss vdd not
xx20 n012 n013 vss vdd not
xx21 n016 n017 vss vdd not
.ends 8_bit_rom_cell

.subckt rom a0 a1 a2 a3 ~cs d0 d1 d2 d3 d4 d5 d6 d7 vdd vss
xx1 a0 a1 a2 a3 sel0 sel1 sel10 sel11 sel12 sel13 sel14 sel15 sel2 sel3 sel4 sel5 sel6 sel7 sel8 sel9 vdd vss 4_to_16_decoder
xx4 sel0 cs3 vdd vss n001 nand
xx2 sel1 cs3 vdd vss n005 nand
xx3 ~cs cs3 cs7 cs11 cs15 vss vdd 1_to_4_not
xxbyte0 n001 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte1 n005 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xx5 sel2 cs3 vdd vss n009 nand
xx6 sel3 cs3 vdd vss n013 nand
xxbyte2 n009 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte3 n013 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xx7 sel4 cs7 vdd vss n002 nand
xx8 sel5 cs7 vdd vss n006 nand
xxbyte4 n002 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte5 n006 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xx9 sel6 cs7 vdd vss n010 nand
xx11 sel7 cs7 vdd vss n014 nand
xxbyte6 n010 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte7 n014 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xx13 sel8 cs11 vdd vss n003 nand
xx14 sel9 cs11 vdd vss n007 nand
xxbyte8 n003 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte9 n007 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xx16 sel10 cs11 vdd vss n011 nand
xx18 sel11 cs11 vdd vss n015 nand
xxbyte10 n011 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte11 n015 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xx20 sel12 cs15 vdd vss n004 nand
xx22 sel13 cs15 vdd vss n008 nand
xxbyte12 n004 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte13 n008 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xx24 sel14 cs15 vdd vss n012 nand
xx26 sel15 cs15 vdd vss n016 nand
xxbyte14 n012 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
xxbyte15 n016 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_rom_cell
.ends rom
