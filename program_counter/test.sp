* program counter test circuit

.include program_counter.inc

xx1 n002 n004 n006 n008 nd0 nd1 nd2 nd3 n001 0 program_counter
vclk n002 0 0
v1 n001 0 5
r1 nd3 n009 0 100k
r2 nd2 n010 0 100k
r3 nd1 n011 0 100k
r4 nd0 n012 0 100k
vce n006 0 0
vie n008 0 0
voe n004 0 0
vd3 n009 0 0
vd2 n010 0 0
vd1 n011 0 0
vd0 n012 0 0

.tran 10ns 125u
.option itl1=300
.end
