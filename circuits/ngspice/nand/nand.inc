* nand gate subcircuit

.include ../mosfet/mosfet.inc

.subckt nand a b vdd vss out
r1 vdd out 1k
xx1 out a n001 vss nmos_4t
xx2 n001 b vss vss nmos_4t
.ends nand
