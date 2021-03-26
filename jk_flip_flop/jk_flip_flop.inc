*  jk flip-flop subcircuit

.include ../sr_latch/sr_latch.inc
.include ../not/not.inc
.include ../and/and.inc
.include ../nand/nand.inc

.subckt 3waynand a b vdd vss out c
m1 out a vdd vdd fds4885c_p
m2 out a n001 n001 si4820dy
m3 out b vdd vdd fds4885c_p
m4 n001 b n002 n002 si4820dy
m5 n002 c vss vss si4820dy
m6 out c vdd vdd fds4885c_p
.ends 3waynand

.subckt 3wayand a b vdd vss out c
xx1 a b vdd vss n001 c 3waynand
xx2 n001 out vss vdd not
.ends 3wayand

.subckt jk_flip_flop clk j k nq q vdd vss
xx1 n003 n007 nq q vdd vss sr_latch
xx2 n002 n005 n006 n001 vdd vss sr_latch
xx4 clk n004 vss vdd not
xx5 n004 n006 vdd vss n007 and
xx6 clk k vdd vss n005 q 3wayand
xx3 n001 n004 vdd vss n003 and
xx7 nq j vdd vss n002 clk 3wayand
.ends jk_flip_flop
