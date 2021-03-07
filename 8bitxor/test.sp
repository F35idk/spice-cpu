* 8-bit xor test circuit

.include 8bitxor.inc

vb4 n022 0 0
vb2 n018 0 5
vb3 n020 0 5
vb5 n023 0 0
vb6 n024 0 0
va6 n010 0 0
va4 n006 0 5
va5 n008 0 5
va7 n012 0 0
vb1 n016 0 5
va2 n004 0 5
va0 n002 0 0
va1 n003 0 0
va3 n005 0 5
vb7 n025 0 0
vb0 n014 0 5
v1 n001 0 5
r1 nout7 0 1k
r2 nout6 0 1k
r3 nout5 0 1k
r4 nout4 0 1k
r5 nout3 0 1k
r6 nout2 0 1k
r7 nout1 0 1k
r8 nout0 0 1k
xx2 n002 n003 n004 n005 n006 n008 n010 n012 n014 n016 n018 n020 n022 n023 n024 n025 nout0 nout1 nout2 nout3 nout4 nout5 nout6 nout7 0 n001 8bitxor

.tran 1ns 100ns
.end
