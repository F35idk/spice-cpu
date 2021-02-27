* not gate test circuit

.include not.inc

v1 n001 0 5
xx1 n002 nout 0 n001 not
r1 nout 0 1k
vin n002 0 0

.tran 1ns 100ns
.end
