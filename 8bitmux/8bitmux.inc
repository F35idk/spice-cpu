* 8-bit mux subcircuit

.include ../mux/mux.inc

.subckt 8bitmux a0 a1 a2 a3 a4 a5 a6 a7 b0 b1 b2 b3 b4 b5 b6 b7 sel out0 out1 out2 out3 out4 out5 out6 out7 vdd vss
xx1 a0 b0 sel out0 vdd vss mux
xx2 a1 b1 sel out1 vdd vss mux
xx3 a2 b2 sel out2 vdd vss mux
xx4 a3 b3 sel out3 vdd vss mux
xx5 a4 b4 sel out4 vdd vss mux
xx6 a5 b5 sel out5 vdd vss mux
xx7 a6 b6 sel out6 vdd vss mux
xx8 a7 b7 sel out7 vdd vss mux
.ends 8bitmux
