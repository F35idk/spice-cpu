* not gate subcircuit

.include ../device_models.inc

.subckt not in out vss vdd
m1 out in vss vss si4820dy
m2 out in vdd vdd fds4885c_p
.ends not
