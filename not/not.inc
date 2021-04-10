* not gate subcircuit

.include ../device_models.inc

.subckt not in out vss vdd
r1 vdd out 1k
xx1 out in vss vss nmos_4t
.ends not

.subckt not_cmos in out vss vdd
m1 out in vss vss si4820dy
m2 out in vdd vdd fds4885c_p
.ends not_cmos
