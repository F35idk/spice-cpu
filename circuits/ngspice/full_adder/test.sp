* full adder test circuit

.include full_adder.inc

v1 n001 0 5
vb n004 0 0
vc n005 0 5
r1 ncarry 0 100k
r2 nsum 0 100k
xx2 n002 n004 n005 ncarry nsum n001 0 full_adder
va n002 0 5

.tran 1ns 100ns
.end
