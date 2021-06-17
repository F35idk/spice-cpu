* schmitt trigger inverter circuit. positive and negative going threshold should be ~3.5V

.include ../device_models.inc

.subckt schmitt_trigger_not in out vss vdd
r1 vdd out 1k
xx1 n001 in vss vss nmos_4t
xx2 out in n001 vss nmos_4t
xx3 vdd out n001 vss nmos_4t
.ends schmitt_trigger_not
