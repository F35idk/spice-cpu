* sr-latch subcurcuit

.include ../nor/nor.inc

.subckt sr_latch r s nq q vdd vss
xx1 q s vdd vss nq nor
xx2 r nq vdd vss q nor
.ends sr_latch
