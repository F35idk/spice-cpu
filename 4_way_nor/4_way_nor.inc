* 4-way nor subcircuit

.include ../device_models.inc

.subckt 4_way_nor a b c d out vdd vss
r1 vdd out 1k
xx1 out a vss vss nmos_4t
xx2 out b vss vss nmos_4t
xx3 out c vss vss nmos_4t
xx4 out d vss vss nmos_4t
.ends 4_way_nor

.subckt 4_way_nor_cmos a b c d out vdd vss
m1 out a vss vss si4820dy
m2 n002 b n001 n001 fds4885c_p
m3 n001 a vdd vdd fds4885c_p
m4 out b vss vss si4820dy
rshunt n003 vss 9e12
m5 out c vss vss si4820dy
m6 out d vss vss si4820dy
m7 out d n003 n003 fds4885c_p
m8 n003 c n002 n002 fds4885c_p
rshunt1 n002 vss 9e12
rshunt2 n001 vss 9e12
.ends 4_way_nor_cmos
