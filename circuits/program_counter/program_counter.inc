* program counter subcircuit

.include ../tri_state_buffer/tri_state_buffer.inc
.include ../nand/nand.inc
.include ../not/not.inc
.include ../nor/nor.inc
.include ../or/or.inc
.include ../1_to_4_buffer/1_to_4_buffer.inc
.include ../dt_flip_flop/dt_flip_flop.inc

.subckt program_counter clk oe ce ie d0 d1 d2 d3 vdd vss rst q0 q1 q2 q3
xx35 q0 d0 vss vdd oe tri_state_buffer
xx36 q1 d1 vss vdd oe tri_state_buffer
xx37 q2 d2 vss vdd oe tri_state_buffer
xx38 q3 d3 vss vdd oe tri_state_buffer
xx3 ce ~ce vss vdd not
xx33 n002 n009 n006 ~ce clk0 vdd vss q0 dt_flip_flop
xx41 n003 n012 n008 n007 clk1 vdd vss q1 dt_flip_flop
xx43 n004 n015 n011 n010 clk2 vdd vss q2 dt_flip_flop
xx42 ce q0 vdd vss n007 nand
xx48 n008 n007 n010 vdd vss or
xx49 n005 n016 n014 n013 clk3 vdd vss q3 dt_flip_flop
xx50 n011 n010 n013 vdd vss or
xx1 ie n001 vss vdd not
xx2 n001 ie0 vss vdd not
xx4 n001 ie1 vss vdd not
r1 vss n014 100k
r2 n006 vss 100k
xx7 clk clk0 clk1 clk2 clk3 vss vdd 1_to_4_buffer
xx5 rst ie0 vdd vss n009 nor
xx6 rst3 ie0 vdd vss n012 nor
xx8 rst3 ie1 vdd vss n015 nor
xx9 rst3 ie1 vdd vss n016 nor
xx10 n017 rst3 vss vdd not
xx13 ~rst d0 vdd vss n002 nand
xx12 rst3 ~rst vss vdd not
xx14 ~rst d1 vdd vss n003 nand
xx15 ~rst d2 vdd vss n004 nand
xx16 ~rst d3 vdd vss n005 nand
xx17 rst n017 vss vdd not
.ends program_counter
