* 4-way nor subcircuit

.include ../device_models.inc

.subckt 4_way_nor a b c d out vdd vss
r1 vdd out 1k
xx1 out a vss vss nmos_4t
xx2 out b vss vss nmos_4t
xx3 out c vss vss nmos_4t
xx4 out d vss vss nmos_4t
.ends 4_way_nor
