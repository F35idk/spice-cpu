* toggleable d flip-flop test circuit

.include dt_flip_flop.inc

v1 n001 0 5
vclk n007 0 0
xx1 n002 n005 nq n003 n007 n001 0 n006 dt_flip_flop
vd n002 0 0
r1 nq 0 100k
v~t n003 0 0
v~ie n005 0 0
r2 n006 0 100k

.tran 1ns 60u
.end
