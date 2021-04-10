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

.subckt 3_way_nand_cmos a b vdd vss out c
m1 out a vdd vdd fds4885c_p
m2 out a n001 n001 si4820dy
m3 out b vdd vdd fds4885c_p
m4 n001 b n002 n002 si4820dy
m5 n002 c vss vss si4820dy
m6 out c vdd vdd fds4885c_p
.ends 3_way_nand_cmos

.subckt 3_way_and_cmos a b vdd vss out c
xx1 a b vdd vss n001 c 3_way_nand
xx2 n001 out vss vdd not
.ends 3_way_and_cmos
