* multiplexer subcircuit

.include ../or/or.inc
.include ../and/and.inc
.include ../not/not.inc

.subckt mux a b sel out vdd vss
xx1 n001 n002 out vdd vss or
xx2 a n003 vdd vss n002 and
xx3 sel n003 vss vdd not
xx4 b sel vdd vss n001 and
.ends mux
