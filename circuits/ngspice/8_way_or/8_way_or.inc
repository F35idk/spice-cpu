* 8-way or subcircuit

.include ../or/or.inc

.subckt 8_way_or in0 in1 in2 in3 in4 in5 in6 in7 out vdd vss
xx1 in0 in1 n001 vdd vss or
xx2 n001 in2 n002 vdd vss or
xx3 n002 in3 n003 vdd vss or
xx4 n003 in4 n004 vdd vss or
xx5 n004 in5 n005 vdd vss or
xx6 n005 in6 n006 vdd vss or
xx7 n006 in7 out vdd vss or
.ends 8_way_or
