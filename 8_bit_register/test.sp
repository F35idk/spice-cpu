* 8-bit register test circuit

.include 8_bit_register.inc

v1 n001 0 5
vq0 n020 0 5
vclk n010 0 5
voe n006 0 5
vie n003 0 5
xx1 n010 n003 n006 nq0 nq1 nq2 nq3 nq4 nq5 nq6 nq7 n001 0 8_bit_register
vq1 n019 0 5
vq2 n018 0 5
vq3 n017 0 5
vq4 n016 0 5
vq5 n015 0 5
vq6 n014 0 5
vq7 n013 0 5
r1 nq7 n013 100
r2 nq6 n014 100
r3 nq5 n015 100
r4 nq4 n016 100
r5 nq3 n017 100
r6 nq2 n018 100
r7 nq1 n019 100
r8 nq0 n020 100

.tran 1ns 201us
.end

