* jk flip-flop test circuit

.include jkflipflop.inc

v1 n001 0 5
vj n002 0 5
vk n004 0 5
xx1 n006 n002 n004 n005 nq n001 0 jk_flip_flop
vclk n006 0 5
r1 nq 0 1k
r2 n005 0 1k

.tran 1ns 201u
.option rshunt=1e12
.end
