* 8-bit register subcircuit

.include ../d_latch/d_latch.inc
.include ../tri_state_buffer/tri_state_buffer.inc
.include ../edge_detector/edge_detector.inc
.include ../nand/nand.inc
.include ../1_to_4_not/1_to_4_not.inc

.subckt tri_state_d_latch d e oe q vdd vss
xx2 d e n002 n001 vdd vss d_latch
xx4 n001 q vss vdd oe tri_state_buffer
r1 n002 vss 400k
r2 q vss 400k
.ends tri_state_d_latch

* block symbol definitions
.subckt 8_bit_register clk ie oe q0 q1 q2 q3 q4 q5 q6 q7 vdd vss
xx9 clk n004 vdd vss edge_detector
xx1 q0 n001 oe q0 vdd vss tri_state_d_latch
xx2 q1 n001 oe q1 vdd vss tri_state_d_latch
xx3 q2 n002 oe q2 vdd vss tri_state_d_latch
xx4 q3 n002 oe q3 vdd vss tri_state_d_latch
xx5 q4 n005 oe q4 vdd vss tri_state_d_latch
xx6 q5 n005 oe q5 vdd vss tri_state_d_latch
xx7 q6 n006 oe q6 vdd vss tri_state_d_latch
xx8 q7 n006 oe q7 vdd vss tri_state_d_latch
xx10 ie n004 vdd vss n003 nand
xx15 n003 n001 n002 n005 n006 vss vdd 1_to_4_not
.ends 8_bit_register
