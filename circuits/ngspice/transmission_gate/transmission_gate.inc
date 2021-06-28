* cmos transmission gate subcircuit

.subckt transmission_gate e in ~e out vdd vss
xx1 out ~e in vdd pmos_4t
xx2 in e out vss nmos_4t
.ends transmission_gate
