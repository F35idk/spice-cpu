* 8-bit register test circuit

.include 8_bit_register.inc

v1 n001 0 5
r1 nq7 0 1k
r2 nq6 0 1k
r3 nq5 0 1k
r4 nq4 0 1k
r5 nq3 0 1k
r6 nq2 0 1k
r7 nq1 0 1k
r8 nq0 0 1k
xx1 n020 n002 n003 n004 n006 n008 n010 n012 n014 n017 n019 nq0 nq1 nq2 nq3 nq4 nq5 nq6 nq7 n001 0 8_bit_register
vd0 n002 0 5
vd1 n003 0 5
vd2 n004 0 5
vd3 n006 0 5
vd4 n008 0 5
vd5 n010 0 5
vd6 n012 0 5
vd7 n014 0 5
vclk n020 0 5
voe n019 0 5
vie n017 0 5

.tran 1ns 201us
.end
