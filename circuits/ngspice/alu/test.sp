* alu test circuit

.include alu.inc

vny n014 0 0
vnx n012 0 0
vf n016 0 5
vcin n018 0 0
vy5 n031 0 5
vy3 n029 0 5
vy4 n030 0 5
vy6 n032 0 5
vy1 n027 0 5
vx7 n001 0 0
vy0 n026 0 5
vy2 n028 0 5
vnout n020 0 0
vy7 n033 0 5
v1 n009 0 5
r1 nzr 0 100k
r2 ncout 0 100k
r3 nq7 0 100k
r4 nq6 0 100k
r5 nq5 0 100k
r6 nq4 0 100k
r7 nq3 0 100k
r8 nq2 0 100k
vx6 n002 0 0
r9 nq1 0 100k
vx3 n005 0 0
vx1 n007 0 0
vx2 n006 0 0
vx4 n004 0 0
vx5 n003 0 0
r10 nq0 0 100k
vx0 n008 0 0
v~oe n022 0 0
xx1 n018 n016 n020 n012 n014 n008 n007 n006 n005 n004 n003 n002 n001 n026 n027 n028 n029 n030 n031 n032 n033 ncout nq0 nq1 nq2 nq3 nq4 nq5 nq6 nq7 n009 0 nzr n022 alu

.option rshunt=10g
.tran 1ns 100ns
.end
