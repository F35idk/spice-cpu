* 16 byte sram test circuit

.include sram.inc

v1 n001 0 5
va0 n012 0 5
vd0 n023 0 5
vd7 n016 0 5
va1 n013 0 5
va2 n014 0 5
va3 n015 0 5
v~we n008 0 5
voe n010 0 5
vd1 n022 0 5
vd2 n021 0 5
vd3 n020 0 5
vd4 n019 0 5
vd5 n018 0 5
vd6 n017 0 5
r1 nd7 n016 100k
r2 nd6 n017 100k
r3 nd5 n018 100k
r4 nd4 n019 100k
r5 nd3 n020 100k
r6 nd2 n021 100k
r7 nd1 n022 100k
r8 nd0 n023 100k
xx1 n012 n013 n014 n015 n010 n008 nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 n001 0 sram

.tran 30ns 120u
.option rshunt=1e9
.option itl1=300
.end
