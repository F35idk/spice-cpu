* edge detector subcircuit

.include ../device_models.inc
.include ../not/not.inc

.subckt edge_detector clk out vdd vss
c1 n003 n002 100n
xx1 n001 n002 vss vdd not
r1 n003 vss 100
r3 out vss 100
d1 n003 out 1n4148
xx2 clk n001 vss vdd not
.ends edge_detector
