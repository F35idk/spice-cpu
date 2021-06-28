* d-latch subcurcuit

.include ../sr_latch/sr_latch.inc
.include ../and/and.inc
.include ../not/not.inc

.subckt d_latch d ~e nq q vdd vss
xx1 n001 n002 nq q vdd vss sr_latch
xx4 d n003 vss vdd not
xx2 d ~e vdd vss n001 nor
xx3 ~e n003 vdd vss n002 nor
.ends d_latch
