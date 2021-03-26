* half adder test circuit

.include half_adder.inc

xx1 n002 n004 ncarry nsum n001 0 half_adder
v1 n001 0 5
va n002 0 5
vb n004 0 0
r1 ncarry 0 1k
r2 nsum 0 1k

.tran 1ns 100ns
.end
