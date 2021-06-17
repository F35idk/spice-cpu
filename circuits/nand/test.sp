* nand gate test circuit

.include nand.inc

v1 n001 0 5
xx1 n002 n004 n001 0 nout nand
r1 nout 0 100k
va n002 0 0
vb n004 0 0

.tran 1ns 100ns
.end
