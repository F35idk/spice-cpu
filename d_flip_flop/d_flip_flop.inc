* d flip-flop subcircuit

.include ../d_latch/d_latch.inc

.subckt d_flip_flop clk d nq q vdd vss
xx1 n001 clk nq q vdd vss d_latch
xx3 d n002 n003 n001 vdd vss d_latch
xx2 clk n002 vss vdd not
r1 n003 vss 100k
.ends d_flip_flop
