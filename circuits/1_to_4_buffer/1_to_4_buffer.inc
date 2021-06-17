* 1 to 4 buffer subcircuit (for buffering/driving purposes)

.include ../not/not.inc
.include ../1_to_4_not/1_to_4_not.inc

.subckt 1_to_4_buffer in out0 out1 out2 out3 vss vdd
xx5 n001 out0 out1 out2 out3 vss vdd 1_to_4_not
xx6 in n001 vss vdd not
.ends 1_to_4_buffer
