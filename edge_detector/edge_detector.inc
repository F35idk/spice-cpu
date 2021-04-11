* edge detector subcircuit

.include ../not/not.inc
.include ../and/and.inc

.subckt edge_detector clk out vdd vss
c1 vss n002 10n
r1 n002 n001 100
xx1 clk n002 vdd vss out and
xx2 clk n001 vss vdd not
.ends edge_detector
