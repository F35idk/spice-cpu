* alu test circuit

.include alu.inc

vny n030 0 0
vnx n028 0 0
vzy n029 0 5
vf n031 0 5
vcin n032 0 0
vy5 n021 0 5
vy3 n017 0 5
vy4 n019 0 5
vy6 n023 0 5
vzx n026 0 5
vy1 n013 0 5
vx7 n009 0 0
vy0 n011 0 0
vy2 n015 0 5
vnout n033 0 0
vy7 n025 0 5
v1 n001 0 5
r1 ncout 0 1k
r2 nout7 0 1k
r3 nout6 0 1k
r4 nout5 0 1k
r5 nout4 0 1k
r6 nout3 0 1k
r7 nout2 0 1k
r8 nout1 0 1k
vx6 n008 0 0
xx1 n032 n031 n033 n028 n030 n002 n003 n004 n005 n006 n007 n008 n009 n011 n013 n015 n017 n019 n021 n023 n025 n026 n029 ncout nout0 nout1 nout2 nout3 nout4 nout5 nout6 nout7 n001 0 alu
r9 nout0 0 1k
vx3 n005 0 0
vx1 n003 0 0
vx2 n004 0 0
vx4 n006 0 0
vx0 n002 0 0
vx5 n007 0 0

.option rshunt=10g
.tran 1ns 100ns
.end
