* 3-way and subcircuit

.include ../3_way_nand/3_way_nand.inc
.include ../not/not.inc

.subckt 3_way_and a b vdd vss out c
xx1 a b vdd vss n001 c 3_way_nand
xx2 n001 out vss vdd not
.ends 3_way_and
