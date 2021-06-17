* and gate test circuit

.include and.inc

xx1 n002 n003 n001 0 nout and
v1 n001 0 5
r1 nout 0 100k
va n002 0 0
vb n003 0 5

.tran 1ns 100ns
.end
