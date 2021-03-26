* 8-bit adder subcircuit

.include ../full_adder/full_adder.inc

.subckt 8_bit_adder a0 a1 a2 a3 a4 a5 a6 a7 b0 b1 b2 b3 b4 b5 b6 b7 carry sum1 sum2 sum3 sum4 sum5 sum6 sum7 sum0 vdd vss c
xx1 b0 a0 c n001 sum0 vdd vss full_adder
xx2 b1 a1 n001 n002 sum1 vdd vss full_adder
xx3 b2 a2 n002 n003 sum2 vdd vss full_adder
xx4 b3 a3 n003 n004 sum3 vdd vss full_adder
xx5 b4 a4 n004 n005 sum4 vdd vss full_adder
xx6 b5 a5 n005 n006 sum5 vdd vss full_adder
xx7 b6 a6 n006 n007 sum6 vdd vss full_adder
xx8 b7 a7 n007 carry sum7 vdd vss full_adder
.ends 8_bit_adder
