* toggleable d flip-flop subcircuit

.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../sr_latch/sr_latch.inc
.include ../not/not.inc
.include ../or/or.inc
.include ../3_way_nand/3_way_nand.inc

.subckt dt_flip_flop d ~ie q ~t clk vdd vss ~q
xx8 n002 n011 n012 n009 vdd vss sr_latch
xx12 n004 clk vdd vss n011 nor
xx13 clk n005 vdd vss n002 nor
xx15 clk n007 vss vdd not
xx14 n012 n007 vdd vss n010 nor
xx16 n007 n009 vdd vss n008 nor
xx17 n008 n010 ~q q vdd vss sr_latch
xx1 n004 n005 vss vdd not
xx4 n001 n003 vdd vss n004 n006 3_way_nand
xx7 ~q ~ie vdd vss n003 ~t 3_way_nand
xx2 ~ie d n006 vdd vss or
xx3 ~q ~t n001 vdd vss or
.ends dt_flip_flop
