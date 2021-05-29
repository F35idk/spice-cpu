* synchronous 2-bit counter subcircuit

.include ../jk_flip_flop/jk_flip_flop.inc
.include ../nand/nand.inc
.include ../and/and.inc

.subckt 2_bit_counter ~clk ~rst q0 q1 vdd vss
xx1 ~clk ~rst vdd n004 q0 vdd vss jk_flip_flop
xx2 ~clk n001 n002 n003 q1 vdd vss jk_flip_flop
xx4 n004 ~rst vdd vss n002 nand
r1 n003 vss 100k
xx5 ~rst q0 vdd vss n001 and
.ends 2_bit_counter
