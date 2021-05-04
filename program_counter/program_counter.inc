* program counter subcircuit

.include ../tri_state_buffer/tri_state_buffer.inc
.include ../jk_flip_flop/jk_flip_flop.inc
.include ../nor/nor.inc
.include ../nand/nand.inc
.include ../not/not.inc
.include ../and/and.inc

.subckt program_counter clk oe ce ie d0 d1 d2 d3 vdd vss
xx19 clk0 j0 k0 n008 out0 vdd vss jk_flip_flop
xx22 clk1 j1 k1 n012 out1 vdd vss jk_flip_flop
xx26 clk2 j2 k2 n009 out2 vdd vss jk_flip_flop
xx34 clk3 j3 k3 n014 out3 vdd vss jk_flip_flop
xx35 out0 d0 vss vdd oe tri_state_buffer
xx36 out1 d1 vss vdd oe tri_state_buffer
xx37 out2 d2 vss vdd oe tri_state_buffer
xx38 out3 d3 vss vdd oe tri_state_buffer
r1 n014 vss 400k
xx43 n001 n004 vss vdd not
xx44 d0 n002 vdd vss n001 nor
xx45 n001 ~ce0 vdd vss j0 nand
xx46 ~ce0 n004 vdd vss k0 nand
xx47 n006 n010 vss vdd not
xx48 d1 n002 vdd vss n006 nor
xx49 n006 ~ce0 vdd vss j1 nand
xx50 ~ce0 n010 vdd vss k1 nand
xx51 n013 n016 vss vdd not
xx52 d2 n002 vdd vss n013 nor
xx53 n013 ~ce1 vdd vss j2 nand
xx54 ~ce1 n016 vdd vss k2 nand
xx55 n018 n020 vss vdd not
xx56 d3 n002 vdd vss n018 nor
xx57 n018 ~ce1 vdd vss j3 nand
xx58 ~ce1 n020 vdd vss k3 nand
xx1 ie n002 vss vdd not
xx2 ce ~ce0 vss vdd not
xx3 ce ~ce1 vss vdd not
xx4 ce ~ce2 vss vdd not
xx8 out0 ~ce2 vdd vss n005 nor
xx5 n005 n007 vdd vss clk1 nor
xx6 clk ie vdd vss n007 and
xx7 ce ie vdd vss n003 nor
xx9 n003 clk vdd vss clk0 nor
xx10 out1 ~ce2 vdd vss n011 nor
xx11 n011 n015 vdd vss clk2 nor
xx12 clk ie vdd vss n015 and
xx13 out2 ~ce2 vdd vss n017 nor
xx14 n017 n019 vdd vss clk3 nor
xx15 clk ie vdd vss n019 and
r2 n012 vss 400k
r3 n008 vss 400k
r4 n009 vss 400k
.ends program_counter
