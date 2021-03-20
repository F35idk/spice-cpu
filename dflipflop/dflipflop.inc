* d flip-flop subcircuit

.include ../dlatch/dlatch.inc

.model 1n4148 d(is=2.52n rs=.568 n=1.752 cjo=4p m=.4 tt=20n iave=200m vpk=75 mfg=onsemi)

.subckt edge_detector clk out vdd vss
c1 n003 n002 100n
xx1 n001 n002 vss vdd not
r1 n003 vss 100
r3 out vss 100
d1 n003 out 1n4148
xx2 clk n001 vss vdd not
.ends edge_detector

.subckt d_flip_flop clk d nq q vdd vss
xx1 d n001 nq q vdd vss d_latch
xx2 clk n001 vdd vss edge_detector
.ends d_flip_flop
