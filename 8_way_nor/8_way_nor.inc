* 8-way nor subcircuit

.include ../or/or.inc
.include ../nor/nor.inc

.subckt 8_way_nor a b c d e f g h out vdd vss
r1 vdd out 1k
xx1 out a vss vss nmos_4t
xx2 out b vss vss nmos_4t
xx3 out c vss vss nmos_4t
xx5 out d vss vss nmos_4t
xx6 out e vss vss nmos_4t
xx7 out f vss vss nmos_4t
xx8 out g vss vss nmos_4t
xx9 out h vss vss nmos_4t
.ends 8_way_nor
