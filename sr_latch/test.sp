* sr-latch test circuit

.include sr_latch.inc

xx1 n002 n004 n005 nq n001 0 sr_latch
v1 n001 0 5
vr n002 0 0
vs n004 0 0
r1 n005 0 1k
r2 nq 0 1k

.tran 1ns 10us
.end
