* 4-way multiplexer test circuit

.include 4_way_mux.inc

v1 n001 0 5
r1 nout 0 100k
va n004 0 0
vsel1 n002 0 0
vsel0 n003 0 0
vb n005 0 0
vc n007 0 0
vd n008 0 0
xx1 n004 n005 n002 nout n001 0 n003 n007 n008 4_way_mux

.tran 1ns 100ns
.end
