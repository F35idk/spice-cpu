*  jk flip-flop subcircuit

.include ../device_models.inc
.include ../sr_latch/sr_latch.inc
.include ../not/not.inc
.include ../and/and.inc
.include ../3_way_and/3_way_and.inc

.subckt jk_flip_flop clk j k nq q vdd vss
xx1 n003 n007 nq q vdd vss sr_latch
xx2 n002 n005 n006 n001 vdd vss sr_latch
xx4 clk n004 vss vdd not
xx5 n004 n006 vdd vss n007 and
xx6 clk k vdd vss n005 q 3_way_and
xx3 n001 n004 vdd vss n003 and
xx7 nq j vdd vss n002 clk 3_way_and
.ends jk_flip_flop
