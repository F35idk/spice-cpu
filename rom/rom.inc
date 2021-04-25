* 16-byte rom subcircuit

.include ../not/not.inc
.include ../buffer/buffer.inc
.include ../nand/nand.inc
.include ../1_to_4_not/1_to_4_not.inc
.include ../4_to_16_decoder/4_to_16_decoder.inc

.subckt transmission_gate e in ~e out vdd vss
xx1 out ~e in vdd pmos_4t
xx2 in e out vss nmos_4t
.ends transmission_gate

.subckt 8_bit_tri_state_buffer ~e in0 in1 in2 in3 in4 in5 in6 in7 out0 out1 out2 out3 out4 out5 out6 out7 vdd vss
xx1 e0 in0 ~e0 out0 vdd vss transmission_gate
xx2 e0 in1 ~e0 out1 vdd vss transmission_gate
xx3 e0 in2 ~e0 out2 vdd vss transmission_gate
xx4 e0 in3 ~e0 out3 vdd vss transmission_gate
xx5 e1 in4 ~e1 out4 vdd vss transmission_gate
xx6 e1 in5 ~e1 out5 vdd vss transmission_gate
xx7 e1 in6 ~e1 out6 vdd vss transmission_gate
xx8 e1 in7 ~e1 out7 vdd vss transmission_gate
xx9 ~e n001 vss vdd not
xx12 n001 e0 vss vdd buffer
xx10 n001 ~e0 vss vdd not
xx11 n001 ~e1 vss vdd not
xx13 n001 e1 vss vdd buffer
.ends 8_bit_tri_state_buffer

.subckt rom a0 a1 a2 a3 ~cs d0 d1 d2 d3 d4 d5 d6 d7 vdd vss
xx1 a0 a1 a2 a3 sel0 sel1 sel10 sel11 sel12 sel13 sel14 sel15 sel2 sel3 sel4 sel5 sel6 sel7 sel8 sel9 vdd vss 4_to_16_decoder
xx4 sel0 cs3 vdd vss n001 nand
xxbyte0 n001 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx2 sel1 cs3 vdd vss n005 nand
xxbyte1 n005 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx6 sel2 cs3 vdd vss n009 nand
xxbyte2 n009 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx8 sel3 cs3 vdd vss n013 nand
xxbyte3 n013 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx10 sel4 cs7 vdd vss n002 nand
xxbyte4 n002 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx12 sel5 cs7 vdd vss n006 nand
xxbyte5 n006 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx15 sel6 cs7 vdd vss n010 nand
xxbyte6 n010 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx17 sel7 cs7 vdd vss n014 nand
xxbyte7 n014 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx19 sel8 cs11 vdd vss n003 nand
xxbyte8 n003 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx21 sel9 cs11 vdd vss n007 nand
xxbyte9 n007 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx23 sel10 cs11 vdd vss n011 nand
xxbyte10 n011 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx25 sel11 cs11 vdd vss n015 nand
xxbyte11 n015 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx27 sel12 cs15 vdd vss n004 nand
xxbyte12 n004 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx29 sel13 cs15 vdd vss n008 nand
xxbyte13 n008 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx31 sel14 cs15 vdd vss n012 nand
xxbyte14 n012 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx33 sel15 cs15 vdd vss n016 nand
xxbyte15 n016 vss vss vss vss vss vss vss vss d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_tri_state_buffer
xx3 ~cs cs3 cs7 cs11 cs15 vss vdd 1_to_4_not
.ends rom
