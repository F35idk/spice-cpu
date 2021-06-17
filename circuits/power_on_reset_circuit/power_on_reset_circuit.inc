* power on reset subcircuit

.include ../schmitt_trigger_not/schmitt_trigger_not.inc
.include ../not/not.inc

.subckt power_on_reset_circuit rst vdd vss
c1 vss n001 100n
r1 vdd n001 55
xx1 n002 n003 vss vdd schmitt_trigger_not
xx2 n003 n004 vss vdd schmitt_trigger_not
xx3 n004 rst vss vdd not
r2 n001 n002 1k
.ends power_on_reset_circuit
