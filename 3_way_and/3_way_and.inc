* 3-way and subcircuit

.include ../not/not.inc
.include ../nand/nand.inc
.include ../device_models.inc

.subckt 3_way_nand a b vdd vss out c
r1 vdd out 1k
xx1 out a n001 vss nmos_4t
xx2 n001 b p001 vss nmos_4t
xx3 p001 c vss vss nmos_4t
.ends 3_way_nand

.subckt 3_way_and a b vdd vss out c
xx1 a b vdd vss n001 c 3_way_nand
xx2 n001 out vss vdd not
.ends 3_way_and
