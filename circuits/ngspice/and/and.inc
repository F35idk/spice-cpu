* and gate subcircuit

.include ../nand/nand.inc
.include ../not/not.inc

.subckt and a b vdd vss out
XX1 a b vdd vss N001 nand
XX2 N001 out vss vdd not
.ends and
