* xor gate test circuit

.include xor.inc

xx1 n002 n004 n001 0 nout xor
v1 n001 0 5
r1 nout 0 1k
vb n004 0 5
va n002 0 5

.tran 1ns 100ns
.end
