* 8-bit mux test circuit

.include 8_bit_mux.inc

vb4 n023 0 0
vb2 n019 0 5
vb3 n021 0 5
vb5 n024 0 0
vb6 n025 0 0
va6 n011 0 0
va4 n007 0 5
va5 n009 0 5
va7 n013 0 0
vb1 n017 0 5
va2 n005 0 5
va0 n003 0 0
va1 n004 0 0
va3 n006 0 5
vb7 n026 0 0
vb0 n015 0 5
v1 n001 0 5
r1 nout7 0 1k
r2 nout6 0 1k
r3 nout5 0 1k
r4 nout4 0 1k
r5 nout3 0 1k
r6 nout2 0 1k
r7 nout1 0 1k
r8 nout0 0 1k
vsel n002 0 5
xx1 n003 n004 n005 n006 n007 n009 n011 n013 n015 n017 n019 n021 n023 n024 n025 n026 n002 nout0 nout1 nout2 nout3 nout4 nout5 nout6 nout7 n001 0 8_bit_mux

.tran 1ns 100ns
.end
