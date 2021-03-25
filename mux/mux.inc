* multiplexer subcircuit

.include ../nand/nand.inc
.include ../not/not.inc

.subckt mux a b sel out vdd vss
xx3 sel n003 vss vdd not
xx1 b sel vdd vss n001 nand
xx2 n001 n002 vdd vss out nand
xx4 a n003 vdd vss n002 nand
.ends mux
