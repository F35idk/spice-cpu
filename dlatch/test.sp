* d-latch test circuit

.include dlatch.inc

v1 n001 0 5
vd n002 0 5
ve n004 0 5
r1 n005 0 1k
r2 nq 0 1k
xx2 n002 n004 n005 nq n001 0 d_latch

.tran 1ns 10us
.end
