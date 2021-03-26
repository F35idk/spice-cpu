* d-latch subcurcuit

.include ../sr_latch/sr_latch.inc
.include ../and/and.inc
.include ../not/not.inc

.subckt d_latch d e nq q vdd vss
xx1 n002 n003 nq q vdd vss sr_latch
xx2 e d vdd vss n003 and
xx3 n001 e vdd vss n002 and
xx4 d n001 vss vdd not
.ends d_latch
