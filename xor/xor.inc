* xor gate subcircuit

.include ../nand/nand.inc
.include ../or/or.inc
.include ../and/and.inc

.subckt xor a b vdd vss out
xx2 a b vdd vss n002 nand
xx1 a b n001 vdd vss or
xx3 n001 n002 vdd vss out and
.ends xor
