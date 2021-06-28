* 8-bit and subcircuit

.include ../and/and.inc

.subckt 8_bit_and a0 a1 a2 a3 a4 a5 a6 a7 b0 b1 b2 b3 b4 b5 b6 b7 out0 out1 out2 out3 out4 out5 out6 out7 vss vdd
xx1 a0 b0 vdd vss out0 and
xx2 a1 b1 vdd vss out1 and
xx3 a2 b2 vdd vss out2 and
xx4 a3 b3 vdd vss out3 and
xx5 a4 b4 vdd vss out4 and
xx6 a5 b5 vdd vss out5 and
xx7 a6 b6 vdd vss out6 and
xx8 a7 b7 vdd vss out7 and
.ends 8_bit_and
