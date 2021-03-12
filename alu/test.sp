* alu test circuit

.include alu.inc

vny n031 0 5
vnx n028 0 5
vzy n030 0 5
vf n032 0 5
vcin n033 0 0
vy5 n021 0 5
vy3 n017 0 5
vy4 n019 0 5
vy6 n023 0 5
vzx n026 0 0
vy1 n013 0 5
vx7 n009 0 0
vy0 n011 0 5
vy2 n015 0 5
vnout n034 0 5
vy7 n025 0 5
v1 n001 0 5
r1 nzr 0 1k
r2 ncout 0 1k
r3 nout7 0 1k
r4 nout6 0 1k
r5 nout5 0 1k
r6 nout4 0 1k
r7 nout3 0 1k
r8 nout2 0 1k
vx6 n008 0 0
r9 nout1 0 1k
vx3 n005 0 0
vx1 n003 0 0
vx2 n004 0 0
vx4 n006 0 0
vx0 n002 0 0
vx5 n007 0 0
r10 nout0 0 1k
xx1 n033 n032 n034 n028 n031 n002 n003 n004 n005 n006 n007 n008 n009 n011 n013 n015 n017 n019 n021 n023 n025 n026 n030 ncout nout0 nout1 nout2 nout3 nout4 nout5 nout6 nout7 n001 0 nzr alu

.option rshunt=10g
.tran 1ns 100ns
.end
