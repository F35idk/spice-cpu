* nor gate test circuit

.include nor.inc

r1 nout 0 1k
v1 n001 0 5
xx1 n002 n004 n001 0 nout nor
va n002 0 0
vb n004 0 0

.tran 1ns 100ns
.end