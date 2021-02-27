* multiplexer test circuit

.include mux.inc

v1 n001 0 5
r1 nout 0 1k
va n003 0 5
vb n005 0 0
xx2 n003 n005 n002 nout n001 0 mux
vsel n002 0 0

.tran 1ns 100ns
.end
