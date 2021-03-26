* d flip-flop test circuit

.include d_flip_flop.inc

v1 n001 0 5
vd n002 0 5
vclk n004 0 5
r1 nq 0 1k
r2 n003 0 1k
xx1 n004 n002 n003 nq n001 0 d_flip_flop

.tran 1ns 200us
.end
