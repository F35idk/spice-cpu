* 8-way nor test circuit

.include 8waynor.inc

r1 nout 0 1k
vin3 n005 0 5
vin1 n003 0 5
vin2 n004 0 5
vin4 n007 0 5
vin5 n008 0 5
vin0 n002 0 5
vin6 n009 0 5
v1 n001 0 5
vin7 n010 0 5
xx1 n002 n003 n004 n005 n007 n008 n009 n010 nout n001 0 8waynor

.tran 1ns 100ns
.end
