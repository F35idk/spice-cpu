* 8-bit register subcircuit

.include ../d_latch/d_latch.inc
.include ../tri_state_buffer/tri_state_buffer.inc
.include ../edge_detector/edge_detector.inc
.include ../nand/nand.inc
.include ../1_to_4_not/1_to_4_not.inc

.subckt tri_state_d_latch d e oe q vdd vss
xx2 d e n001 q vdd vss d_latch
xx4 q d vss vdd oe tri_state_buffer
r1 n001 vss 400k
r2 d vss 400k
.ends tri_state_d_latch

.subckt 8_bit_register clk ie oe d0 d1 d2 d3 d4 d5 d6 d7 q0 q1 q2 q3 q4 q5 q6 q7 vdd vss
xx10 ie n004 vdd vss n003 nand
xx15 n003 n001 n002 n005 n006 vss vdd 1_to_4_not
xx9 clk n004 vdd vss edge_detector
xx1 d0 n001 oe q0 vdd vss tri_state_d_latch
xx2 d1 n001 oe q1 vdd vss tri_state_d_latch
xx3 d2 n002 oe q2 vdd vss tri_state_d_latch
xx4 d3 n002 oe q3 vdd vss tri_state_d_latch
xx5 d4 n005 oe q4 vdd vss tri_state_d_latch
xx6 d5 n005 oe q5 vdd vss tri_state_d_latch
xx7 d6 n006 oe q6 vdd vss tri_state_d_latch
xx8 d7 n006 oe q7 vdd vss tri_state_d_latch
.ends 8_bit_register
