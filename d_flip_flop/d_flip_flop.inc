* d flip-flop subcircuit

.include ../d_latch/d_latch.inc
.include ../edge_detector/edge_detector.inc

.subckt d_flip_flop clk d nq q vdd vss
xx1 d n001 nq q vdd vss d_latch
xx2 clk n001 vdd vss edge_detector
.ends d_flip_flop
