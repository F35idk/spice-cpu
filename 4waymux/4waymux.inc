* 4-way multiplexer subcircuit

.include ../mux/mux.inc

.subckt 4waymux a b sel1 out vdd vss sel0 c d
xx1 a b sel0 n001 vdd vss mux
xx2 c d sel0 n002 vdd vss mux
xx3 n001 n002 sel1 out vdd vss mux
.ends 4waymux
