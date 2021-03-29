* 8-bit register subcircuit

.include ../d_latch/d_latch.inc
.include ../tri_state_buffer/tri_state_buffer.inc
.include ../edge_detector/edge_detector.inc
.include ../and/and.inc

.subckt tri_state_d_latch d e oe q vdd vss
xx2 d e n002 n001 vdd vss d_latch
xx4 n001 q vss vdd oe tri_state_buffer
r1 n002 vss 400k
r2 q vss 400k
.ends tri_state_d_latch

.subckt 8_bit_register clk d0 d1 d2 d3 d4 d5 d6 d7 ie oe q0 q1 q2 q3 q4 q5 q6 q7 vdd vss
xx9 clk n002 vdd vss edge_detector
xx10 ie n002 vdd vss n001 and
xx1 d0 n001 oe q0 vdd vss tri_state_d_latch
xx2 d1 n001 oe q1 vdd vss tri_state_d_latch
xx3 d2 n001 oe q2 vdd vss tri_state_d_latch
xx4 d3 n001 oe q3 vdd vss tri_state_d_latch
xx5 d4 n001 oe q4 vdd vss tri_state_d_latch
xx6 d5 n001 oe q5 vdd vss tri_state_d_latch
xx7 d6 n001 oe q6 vdd vss tri_state_d_latch
xx8 d7 n001 oe q7 vdd vss tri_state_d_latch
.ends 8_bit_register
