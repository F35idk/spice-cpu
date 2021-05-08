* 8-bit register test circuit

.include 8_bit_register.inc

v1 n001 0 5
vd0 n028 0 5
vclk n020 0 0
v~oe n019 0 0
vie n018 0 0
r1 nd7 n021 100k
vd7 n021 0 0
r2 nd6 n022 100k
r3 nd5 n023 100k
r4 nd4 n024 100k
r5 nd3 n025 100k
r6 nd2 n026 100k
r7 nd1 n027 100k
r8 nd0 n028 100k
vd1 n027 0 5
vd2 n026 0 5
vd3 n025 0 5
vd4 n024 0 5
vd5 n023 0 5
vd6 n022 0 5
xx1 n020 n018 n019 nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 nq0 nq1 nq2 nq3 nq4 nq5 nq6 nq7 n001 0 8_bit_register
r9 nq0 0 100k
r10 nq1 0 100k
r11 nq2 0 100k
r12 nq3 0 100k
r13 nq4 0 100k
r14 nq5 0 100k
r15 nq6 0 100k
r16 nq7 0 100k

.tran 10ns 490us
.end
