* 1 to 4 buffer subcircuit (for buffering/driving purposes)

.include ../buffer/buffer.inc

.subckt 1_to_4_buffer in out0 out1 out2 out3 vss vdd
xx1 in out0 vss vdd buffer
xx2 in out1 vss vdd buffer
xx3 in out2 vss vdd buffer
xx4 in out3 vss vdd buffer
.ends 1_to_4_buffer
