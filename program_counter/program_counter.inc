* program counter subcircuit

.include ../tri_state_buffer/tri_state_buffer.inc
.include ../jk_flip_flop/jk_flip_flop.inc
.include ../nand/nand.inc
.include ../not/not.inc
.include ../and/and.inc
.include ../1_to_4_buffer/1_to_4_buffer.inc

.subckt program_counter clk oe ce ie d0 d1 d2 d3 vdd vss
xx35 out0 d0 vss vdd oe tri_state_buffer
xx36 out1 d1 vss vdd oe tri_state_buffer
xx37 out2 d2 vss vdd oe tri_state_buffer
xx38 out3 d3 vss vdd oe tri_state_buffer
xx1 n019 n010 n022 n024 out0 vdd vss jk_flip_flop
xx5 n019 n008 n015 n017 out1 vdd vss jk_flip_flop
r5 n017 vss 100k
r1 n024 vss 100k
xx7 n019 n005 n023 n026 out2 vdd vss jk_flip_flop
r3 n026 vss 100k
xx20 out0 out1 vdd vss n001 and
xx15 n001 out2 vdd vss n021 and
xx21 n019 n007 n014 n016 out3 vdd vss jk_flip_flop
r2 n016 vss 100k
xx22 clk n019 vss vdd not
xx4 n004 ie0 vdd vss n020 nand
xx26 n020 n028 vdd vss n015 nand
xx27 n008 ce0 vdd vss n028 nand
xx28 ce0 out0 vdd vss n011 nand
xx29 n004 n011 vdd vss n008 nand
xx30 ie0 d1 vdd vss n004 nand
xx6 n002 ie1 vdd vss n013 nand
xx8 n013 n025 vdd vss n023 nand
xx9 n005 ce1 vdd vss n025 nand
xx10 ce1 n001 vdd vss n006 nand
xx11 n002 n006 vdd vss n005 nand
xx12 ie1 d2 vdd vss n002 nand
xx14 n003 ie3 vdd vss n018 nand
xx16 n018 n027 vdd vss n014 nand
xx17 n007 ce2 vdd vss n027 nand
xx18 ce2 n021 vdd vss n009 nand
xx19 n003 n009 vdd vss n007 nand
xx31 ie2 d3 vdd vss n003 nand
xx3 ce ~ce vss vdd not
xx2 ~ce ce0 vss vdd not
xx13 ~ce ce1 vss vdd not
xx33 ~ce ce2 vss vdd not
xx34 ie ie0 ie1 ie2 ie3 vss vdd 1_to_4_buffer
xx32 d0 ie3 vdd vss n012 nand
xx39 ~ce n012 vdd vss n010 nand
xx40 n012 ie3 vdd vss n029 nand
xx41 n029 ~ce vdd vss n022 nand
.ends program_counter
