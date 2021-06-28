* demultiplexer subcircuit

.include ../and/and.inc
.include ../not/not.inc

.subckt dmux in sel a b vdd vss
xx1 in sel vdd vss b and
xx2 sel n001 vss vdd not
xx3 in n001 vdd vss a and
.ends dmux
