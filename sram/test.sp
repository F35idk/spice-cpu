* 16 byte sram test circuit

.include sram.inc

v1 n001 0 5
va0 n003 0 5
vd0 n024 0 5
vd7 n017 0 5
va1 n005 0 5
va2 n007 0 5
va3 n009 0 5
vclk n015 0 5
vwe n011 0 5
vcs n013 0 5
xx1 n003 n005 n007 n009 n015 n013 n011 nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 n001 0 sram
vd1 n023 0 5
vd2 n022 0 5
vd3 n021 0 5
vd4 n020 0 5
vd5 n019 0 5
vd6 n018 0 5
r1 nd7 n017 100k
r2 nd6 n018 100k
r3 nd5 n019 100k
r4 nd4 n020 100k
r5 nd3 n021 100k
r6 nd2 n022 100k
r7 nd1 n023 100k
r8 nd0 n024 100k

.tran 30ns 141u
.option itl1=300
.end

