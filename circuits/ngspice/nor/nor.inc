* nor gate subcircuit

.include ../mosfet/mosfet.inc

.subckt nor a b vdd vss out
r1 vdd out 1k
xx1 out a vss vss nmos_4t
xx2 out b vss vss nmos_4t
.ends nor
