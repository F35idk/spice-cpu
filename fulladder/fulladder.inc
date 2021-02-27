* full adder subcircuit

.include ../xor/xor.inc
.include ../and/and.inc
.include ../or/or.inc

.subckt fulladder a b c carry sum vdd vss
xx1 a b vdd vss n001 xor
xx2 b a vdd vss n002 and
xx4 n001 c vdd vss n003 and
xx5 n001 c vdd vss sum xor
xx3 n002 n003 carry vdd vss or
.ends fulladder
