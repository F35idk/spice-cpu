* toggleable d flip-flop subcircuit

.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../sr_latch/sr_latch.inc
.include ../not/not.inc

.subckt dt_flip_flop d ~ie q ~t clk vdd vss ~q
xx8 n002 n009 n010 n007 vdd vss sr_latch
xx12 n011 clk vdd vss n009 nor
xx13 clk n003 vdd vss n002 nor
xx15 clk n005 vss vdd not
xx14 n010 n005 vdd vss n008 nor
xx16 n005 n007 vdd vss n006 nor
xx17 n006 n008 ~q q vdd vss sr_latch
xx1 n001 n004 vdd vss n003 nor
xx5 ~q ~t vdd vss n001 nor
xx9 ~ie d vdd vss n004 nor
xx6 ~ie ~t vdd vss n012 nand
xx7 n003 n012 vdd vss n011 nand
.ends dt_flip_flop
