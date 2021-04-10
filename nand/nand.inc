* nand gate subcircuit

.include ../device_models.inc

.subckt nand a b vdd vss out
r1 vdd out 1k
xx1 out a n001 vss nmos_4t
xx2 n001 b vss vss nmos_4t
.ends nand

.subckt nand_cmos a b vdd vss out
m1 out a vdd vdd fds4885c_p
m2 out a n001 n001 si4820dy
m3 out b vdd vdd fds4885c_p
m4 n001 b vss vss si4820dy
.ends nand_cmos
