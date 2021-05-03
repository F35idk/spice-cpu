* alu test circuit

.include alu.inc

vny n031 0 5
vnx n028 0 5
v~zy n030 0 5
vf n032 0 5
vcin n033 0 0
vy5 n021 0 5
vy3 n017 0 5
vy4 n019 0 5
vy6 n023 0 5
v~zx n026 0 0
vy1 n013 0 5
vx7 n009 0 0
vy0 n011 0 5
vy2 n015 0 5
vnout n034 0 5
vy7 n025 0 5
v1 n001 0 5
r1 nzr 0 100k
r2 ncout 0 100k
r3 nq7 0 100k
r4 nq6 0 100k
r5 nq5 0 100k
r6 nq4 0 100k
r7 nq3 0 100k
r8 nq2 0 100k
vx6 n008 0 0
r9 nq1 0 100k
vx3 n005 0 0
vx1 n003 0 0
vx2 n004 0 0
vx4 n006 0 0
vx0 n002 0 0
vx5 n007 0 0
r10 nq0 0 100k
xx1 n033 n032 n034 n028 n031 n002 n003 n004 n005 n006 n007 n008 n009 n011 n013 n015 n017 n019 n021 n023 n025 n026 n030 ncout nq0 nq1 nq2 nq3 nq4 nq5 nq6 nq7 n001 0 nzr alu

.option rshunt=10g
.tran 1ns 100ns
.end
