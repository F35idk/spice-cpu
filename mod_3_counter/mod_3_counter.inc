* synchronous mod 3 counter subcircuit

.include ../jk_flip_flop/jk_flip_flop.inc
.include ../nand/nand.inc
.include ../and/and.inc

.subckt mod_3_counter ~clk rst q0 q1 vdd vss
xx1 ~clk n003 vdd n006 q0 vdd vss jk_flip_flop
xx2 ~clk n004 n005 n001 q1 vdd vss jk_flip_flop
xx4 n003 n006 vdd vss n005 nand
xx5 n003 q0 vdd vss n004 and
xx3 n001 q0 vdd vss n002 nor
xx6 n002 rst vdd vss n003 nor
.ends mod_3_counter
