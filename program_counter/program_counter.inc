* program counter subcircuit

.include ../tri_state_buffer/tri_state_buffer.inc
.include ../jk_flip_flop/jk_flip_flop.inc
.include ../nor/nor.inc
.include ../nand/nand.inc
.include ../not/not.inc

.subckt program_counter clk oe ce ie d0 d1 d2 d3 vdd vss
xx19 clk0 j0 k0 ~out0 out0 vdd vss jk_flip_flop
xx22 clk1 j1 k1 ~out1 out1 vdd vss jk_flip_flop
xx26 clk2 j2 k2 ~out2 out2 vdd vss jk_flip_flop
xx34 clk3 j3 k3 n006 out3 vdd vss jk_flip_flop
xx35 out0 d0 vss vdd oe tri_state_buffer
xx36 out1 d1 vss vdd oe tri_state_buffer
xx37 out2 d2 vss vdd oe tri_state_buffer
xx38 out3 d3 vss vdd oe tri_state_buffer
r1 n006 vss 400k
xx39 clk ~ce2 vdd vss clk0 nor
xx40 ~out0 ~ce2 vdd vss clk1 nor
xx41 ~out1 ~ce2 vdd vss clk2 nor
xx42 ~out2 ~ce2 vdd vss clk3 nor
xx43 n001 n003 vss vdd not
xx44 d0 n002 vdd vss n001 nor
xx45 n001 ~ce0 vdd vss j0 nand
xx46 ~ce0 n003 vdd vss k0 nand
xx47 n004 n005 vss vdd not
xx48 d1 n002 vdd vss n004 nor
xx49 n004 ~ce0 vdd vss j1 nand
xx50 ~ce0 n005 vdd vss k1 nand
xx51 n007 n008 vss vdd not
xx52 d2 n002 vdd vss n007 nor
xx53 n007 ~ce1 vdd vss j2 nand
xx54 ~ce1 n008 vdd vss k2 nand
xx55 n009 n010 vss vdd not
xx56 d3 n002 vdd vss n009 nor
xx57 n009 ~ce1 vdd vss j3 nand
xx58 ~ce1 n010 vdd vss k3 nand
xx59 clk clk0 vss vdd ie tri_state_buffer
xx61 clk clk1 vss vdd ie tri_state_buffer
xx62 clk clk2 vss vdd ie tri_state_buffer
xx63 clk clk3 vss vdd ie tri_state_buffer
xx1 ie n002 vss vdd not
xx2 ce ~ce0 vss vdd not
xx3 ce ~ce1 vss vdd not
xx4 ce ~ce2 vss vdd not
.ends program_counter
