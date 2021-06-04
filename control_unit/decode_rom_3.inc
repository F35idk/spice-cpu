* decode rom 3

.include ../nand/nand.inc
.include ../1_to_4_not/1_to_4_not.inc
.include ../4_to_16_decoder/4_to_16_decoder.inc
.include 8_bit_transmission_gate.inc

.subckt decode_rom_3 a0 a1 a2 a3 ~cs d0 d1 d2 d3 d4 d5 d6 d7 vdd vss
xx1 a0 a1 a2 a3 sel0 sel1 sel10 sel11 sel12 sel13 sel14 sel15 sel2 sel3 sel4 sel5 sel6 sel7 sel8 sel9 vdd vss 4_to_16_decoder
xx4 sel0 cs3 vdd vss n001 nand
xxbyte0 n001 vss vdd vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx2 sel1 cs3 vdd vss n005 nand
xxbyte1 n005 vdd vdd vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx6 sel2 cs3 vdd vss n009 nand
xxbyte2 n009 vss vdd vdd vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx8 sel3 cs3 vdd vss n013 nand
xxbyte3 n013 vss vss vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx10 sel4 cs7 vdd vss n002 nand
xxbyte4 n002 vss vdd vss vdd vdd vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx12 sel5 cs7 vdd vss n006 nand
xxbyte5 n006 vss vdd vss vss vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx15 sel6 cs7 vdd vss n010 nand
xxbyte6 n010 vdd vss vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx17 sel7 cs7 vdd vss n014 nand
xxbyte7 n014 vdd vdd vss vss vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx19 sel8 cs11 vdd vss n003 nand
xxbyte8 n003 vss vss vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx21 sel9 cs11 vdd vss n007 nand
xxbyte9 n007 vss vss vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx23 sel10 cs11 vdd vss n011 nand
xxbyte10 n011 vss vss vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx25 sel11 cs11 vdd vss n015 nand
xxbyte11 n015 vss vss vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx27 sel12 cs15 vdd vss n004 nand
xxbyte12 n004 vss vdd vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx29 sel13 cs15 vdd vss n008 nand
xxbyte13 n008 vss vdd vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx31 sel14 cs15 vdd vss n012 nand
xxbyte14 n012 vss vdd vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx33 sel15 cs15 vdd vss n016 nand
xxbyte15 n016 vss vdd vss vdd vss vdd vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_transmission_gate
xx3 ~cs cs3 cs7 cs11 cs15 vss vdd 1_to_4_not
.ends decode_rom_3
