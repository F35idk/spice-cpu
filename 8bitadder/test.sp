* 8-bit adder test circuit

.include 8bitadder.inc

r1 ncarry 0 1k
vb4 n023 0 5
vb2 n020 0 5
vb3 n022 0 5
vb5 n024 0 5
vb6 n025 0 5
xx2 n002 n003 n004 n006 n008 n010 n012 n014 n016 n018 n020 n022 n023 n024 n025 n026 ncarry nsum1 nsum2 nsum3 nsum4 nsum5 nsum6 nsum7 nsum0 n001 0 8bitadder
va6 n012 0 5
va4 n008 0 5
va5 n010 0 5
va7 n014 0 5
vb1 n018 0 5
va2 n004 0 0
va0 n002 0 0
va1 n003 0 0
va3 n006 0 0
vb7 n026 0 5
vb0 n016 0 5
v1 n001 0 5
r2 nsum7 0 1k
r3 nsum6 0 1k
r4 nsum5 0 1k
r5 nsum4 0 1k
r6 nsum3 0 1k
r7 nsum2 0 1k
r8 nsum1 0 1k
r9 nsum0 0 1k

.tran 1ns 100ns
.end
