* program counter test circuit

.include program_counter.inc

vclk n002 0 5
v2 n001 0 5
r1 nd3 n011 100k
r2 nd2 n012 100k
r3 nd1 n013 100k
r4 nd0 n014 100k
vce n006 0 5
vie n008 0 0
voe n004 0 5
vd3 n011 0 0
vd2 n012 0 0
vd1 n013 0 0
vd0 n014 0 0
xx1 n002 n004 n006 n008 nd0 nd1 nd2 nd3 n001 0 n010 program_counter
vrst n010 0 0

.tran 10ns 165u
.option itl1=300
.end
