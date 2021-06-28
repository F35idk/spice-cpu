* not gate subcircuit

.include ../mosfet/mosfet.inc

.subckt not in out vss vdd
r1 vdd out 1k
xx1 out in vss vss nmos_4t
.ends not
