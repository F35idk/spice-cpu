* d flip-flop subcircuit

.include ../d_latch/d_latch.inc

.subckt d_flip_flop clk d nq q vdd vss
xx1 n001 n003 nq q vdd vss d_latch
xx3 d clk n002 n001 vdd vss d_latch
xx2 clk n003 vss vdd not
r1 n002 vss 100k
.ends d_flip_flop
