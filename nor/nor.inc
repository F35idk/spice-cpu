* nor gate subcircuit

.include ../device_models.inc

.subckt nor a b vdd vss out
m1 out a vss vss si4820dy
m2 out b n001 n001 fds4885c_p
m3 n001 a vdd vdd fds4885c_p
m4 out b vss vss si4820dy
rshunt n001 vss 1e12
.ends nor
