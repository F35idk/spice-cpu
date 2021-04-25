* 1 to 4 not subcircuit (for buffering/driving purposes)

.include ../not/not.inc

.subckt 1_to_4_not in out0 out1 out2 out3 vss vdd
xx1 in out0 vss vdd not
xx2 in out1 vss vdd not
xx3 in out2 vss vdd not
xx4 in out3 vss vdd not
.ends 1_to_4_not
