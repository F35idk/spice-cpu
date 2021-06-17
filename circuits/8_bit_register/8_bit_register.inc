* 8-bit register subcircuit

.include ../tri_state_buffer/tri_state_buffer.inc
.include ../d_flip_flop/d_flip_flop.inc
.include ../1_to_4_not/1_to_4_not.inc
.include ../clock_gate/clock_gate.inc

.subckt tri_state_d_flip_flop d clk oe q vdd vss
xx4 q d vss vdd oe tri_state_buffer
r1 n001 vss 400k
r2 d vss 400k
xx1 clk d n001 q vdd vss d_flip_flop
.ends tri_state_d_flip_flop

.subckt 8_bit_register clk ie ~oe d0 d1 d2 d3 d4 d5 d6 d7 q0 q1 q2 q3 q4 q5 q6 q7 vdd vss
xx15 n003 n001 n002 n004 n005 vss vdd 1_to_4_not
xx11 ~oe oe0 oe1 oe2 oe3 vss vdd 1_to_4_not
xx1 d0 n001 oe0 q0 vdd vss tri_state_d_flip_flop
xx4 d1 n001 oe0 q1 vdd vss tri_state_d_flip_flop
xx5 d2 n002 oe1 q2 vdd vss tri_state_d_flip_flop
xx6 d3 n002 oe1 q3 vdd vss tri_state_d_flip_flop
xx7 d4 n004 oe2 q4 vdd vss tri_state_d_flip_flop
xx8 d5 n004 oe2 q5 vdd vss tri_state_d_flip_flop
xx9 d6 n005 oe3 q6 vdd vss tri_state_d_flip_flop
xx10 d7 n005 oe3 q7 vdd vss tri_state_d_flip_flop
xx2 clk ie vdd vss n003 clock_gate
.ends 8_bit_register
