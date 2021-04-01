* 4 to 16 decoder subcircuit

.include ../not/not.inc
.include ../4_way_nor/4_way_nor.inc

.subckt 4_to_16_decoder a b c d d0 d1 d10 d11 d12 d13 d14 d15 d2 d3 d4 d5 d6 d7 d8 d9 vdd vss
xx1 a n001 vss vdd not
xx2 b n002 vss vdd not
xx3 c n003 vss vdd not
xx4 d n004 vss vdd not
xx5 a b c d d0 vdd vss 4_way_nor
xx6 n001 b c d d1 vdd vss 4_way_nor
xx7 a n002 c d d2 vdd vss 4_way_nor
xx8 n001 n002 c d d3 vdd vss 4_way_nor
xx9 a b n003 d d4 vdd vss 4_way_nor
xx10 n001 b n003 d d5 vdd vss 4_way_nor
xx11 a n002 n003 d d6 vdd vss 4_way_nor
xx12 n001 n002 n003 d d7 vdd vss 4_way_nor
xx13 a b c n004 d8 vdd vss 4_way_nor
xx14 n001 b c n004 d9 vdd vss 4_way_nor
xx15 a n002 c n004 d10 vdd vss 4_way_nor
xx16 n001 n002 c n004 d11 vdd vss 4_way_nor
xx17 a b n003 n004 d12 vdd vss 4_way_nor
xx18 n001 b n003 n004 d13 vdd vss 4_way_nor
xx19 a n002 n003 n004 d14 vdd vss 4_way_nor
xx20 n001 n002 n003 n004 d15 vdd vss 4_way_nor
.ends 4_to_16_decoder
