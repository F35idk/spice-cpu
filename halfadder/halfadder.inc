* half adder subcircuit

.include ../xor/xor.inc
.include ../and/and.inc

.subckt halfadder a b carry sum vdd vss
xx1 a b vdd vss sum xor
xx2 b a vdd vss carry and
.ends halfadder
