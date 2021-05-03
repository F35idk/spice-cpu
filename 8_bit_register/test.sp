* 8-bit register test circuit

.include 8_bit_register.inc

v1 n001 0 5
vd0 n020 0 5
vclk n010 0 5
voe n006 0 5
vie n003 0 5
xx1 n010 n003 n006 nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 n001 0 8_bit_register
vd1 n019 0 5
vd2 n018 0 5
vd3 n017 0 5
vd4 n016 0 5
vd5 n015 0 5
vd6 n014 0 5
vd7 n013 0 5
r1 nd7 n013 100k
r2 nd6 n014 100k
r3 nd5 n015 100k
r4 nd4 n016 100k
r5 nd3 n017 100k
r6 nd2 n018 100k
r7 nd1 n019 100k
r8 nd0 n020 100k

.tran 10ns 490us
.end

