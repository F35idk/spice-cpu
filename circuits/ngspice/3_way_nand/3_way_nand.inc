* 3-way nand subcircuit

.include ../mosfet/mosfet.inc

.subckt 3_way_nand a b vdd vss out c
r1 vdd out 1k
xx1 out a n001 vss nmos_4t
xx2 n001 b p001 vss nmos_4t
xx3 p001 c vss vss nmos_4t
.ends 3_way_nand
