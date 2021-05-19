* simple clock gating subcircuit using a falling edge-triggered d-latch and a NAND gate

.include ../d_latch/d_latch.inc
.include ../nand/nand.inc

.subckt clock_gate clk e vdd vss ~clk
r1 n002 vss 100k
xx2 e clk n002 n001 vdd vss d_latch
xx1 clk n001 vdd vss ~clk nand
.ends clock_gate
