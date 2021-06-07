* program counter subcircuit

.include ../tri_state_buffer/tri_state_buffer.inc
.include ../jk_flip_flop/jk_flip_flop.inc
.include ../nand/nand.inc
.include ../not/not.inc
.include ../and/and.inc
.include ../1_to_4_buffer/1_to_4_buffer.inc
.include ../3_way_nand/3_way_nand.inc

.subckt program_counter clk oe ce ie d0 d1 d2 d3 vdd vss rst q0 q1 q2 q3
xx35 q0 d0 vss vdd oe tri_state_buffer
xx36 q1 d1 vss vdd oe tri_state_buffer
xx37 q2 d2 vss vdd oe tri_state_buffer
xx38 q3 d3 vss vdd oe tri_state_buffer
xx1 n017 n009 n020 n023 q0 vdd vss jk_flip_flop
xx5 n017 n007 n014 n015 q1 vdd vss jk_flip_flop
r5 n015 vss 100k
r1 n023 vss 100k
xx7 n022 n005 n025 n027 q2 vdd vss jk_flip_flop
r3 n027 vss 100k
xx20 q0 q1 vdd vss n001 and
xx15 n001 q2 vdd vss n024 and
xx21 n022 n010 n018 n019 q3 vdd vss jk_flip_flop
r2 n019 vss 100k
xx22 clk n017 vss vdd not
xx4 n003 ie0 vdd vss n016 nand
xx27 n007 ce0 vdd vss n029 nand
xx28 ce0 q0 vdd vss n008 nand
xx30 ie0 d1 vdd vss n003 nand
xx3 ce ~ce vss vdd not
xx2 ~ce ce0 vss vdd not
xx13 ~ce ce1 vss vdd not
xx34 ie ie0 ie1 ie2 ie3 vss vdd 1_to_4_buffer
xx32 d0 ie3 vdd vss n011 nand
xx39 ~ce n011 vdd vss n009 nand
xx40 n011 ie3 vdd vss n028 nand
xx23 n016 ~rst3 vdd vss n014 n029 3_way_nand
xx10 ce0 n001 vdd vss n006 nand
xx11 ie1 d2 vdd vss n002 nand
xx6 n002 ie1 vdd vss n013 nand
xx8 n005 ce1 vdd vss n026 nand
xx25 n013 ~rst3 vdd vss n025 n026 3_way_nand
xx12 ce1 n024 vdd vss n012 nand
xx18 ie2 d3 vdd vss n004 nand
xx14 n004 ie3 vdd vss n021 nand
xx16 n010 ce1 vdd vss n030 nand
xx17 n021 ~rst3 vdd vss n018 n030 3_way_nand
xx24 n003 n008 vdd vss n007 nand
xx9 n002 n006 vdd vss n005 nand
xx19 n004 n012 vdd vss n010 nand
xx26 n028 ~ce vdd vss n020 ~rst3 3_way_nand
xx29 rst ~rst3 vss vdd not
xx31 clk n022 vss vdd not
.ends program_counter
