* or gate subcircuit

.include ../nor/nor.inc
.include ../not/not.inc

.subckt or a b out vdd vss
xx1 a b vdd vss n001 nor
xx2 n001 out vss vdd not
.ends or
