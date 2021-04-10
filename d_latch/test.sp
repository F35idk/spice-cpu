* d-latch test circuit

.include d_latch.inc

v1 n001 0 5
vd n002 0 5
ve n004 0 5
r1 n005 0 100k
r2 nq 0 100k
xx2 n002 n004 n005 nq n001 0 d_latch

.tran 1ns 10us
.end
