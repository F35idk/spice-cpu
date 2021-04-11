* 4 to 16 decoder subcircuit

.include ../not/not.inc
.include ../buffer/buffer.inc
.include ../4_way_nor/4_way_nor.inc

.subckt 4_to_16_decoder a b c d d0 d1 d10 d11 d12 d13 d14 d15 d2 d3 d4 d5 d6 d7 d8 d9 vdd vss
xx3 a ~a_1 vss vdd not
xx4 a ~a_2 vss vdd not
xx2 a a_2 vss vdd buffer
xx1 a a_1 vss vdd buffer
xx5 b ~b_1 vss vdd not
xx6 b ~b_2 vss vdd not
xx7 b b_2 vss vdd buffer
xx8 b b_1 vss vdd buffer
xx9 c ~c_1 vss vdd not
xx10 c ~c_2 vss vdd not
xx11 c c_2 vss vdd buffer
xx12 c c_1 vss vdd buffer
xx13 d ~d_1 vss vdd not
xx14 d ~d_2 vss vdd not
xx15 d d_2 vss vdd buffer
xx16 d d_1 vss vdd buffer
xx17 a_1 b_1 c_1 d_1 d0 vdd vss 4_way_nor
xx18 ~a_1 b_1 c_1 d_1 d1 vdd vss 4_way_nor
xx19 a_1 ~b_1 c_1 d_1 d2 vdd vss 4_way_nor
xx20 ~a_1 ~b_1 c_1 d_1 d3 vdd vss 4_way_nor
xx21 a_1 b_1 ~c_1 d_2 d4 vdd vss 4_way_nor
xx22 ~a_1 b_1 ~c_1 d_2 d5 vdd vss 4_way_nor
xx23 a_1 ~b_1 ~c_1 d_2 d6 vdd vss 4_way_nor
xx24 ~a_1 ~b_1 ~c_1 d_2 d7 vdd vss 4_way_nor
xx25 a_2 b_2 c_2 ~d_1 d8 vdd vss 4_way_nor
xx26 ~a_2 b_2 c_2 ~d_1 d9 vdd vss 4_way_nor
xx27 a_2 ~b_2 c_2 ~d_1 d10 vdd vss 4_way_nor
xx28 ~a_2 ~b_2 c_2 ~d_1 d11 vdd vss 4_way_nor
xx29 a_2 b_2 ~c_2 ~d_2 d12 vdd vss 4_way_nor
xx30 ~a_2 b_2 ~c_2 ~d_2 d13 vdd vss 4_way_nor
xx31 a_2 ~b_2 ~c_2 ~d_2 d14 vdd vss 4_way_nor
xx32 ~a_2 ~b_2 ~c_2 ~d_2 d15 vdd vss 4_way_nor
.ends 4_to_16_decoder
