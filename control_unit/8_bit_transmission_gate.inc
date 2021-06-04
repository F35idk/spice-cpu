.include ../transmission_gate/transmission_gate.inc
.include ../not/not.inc
.include ../buffer/buffer.inc

.subckt 8_bit_transmission_gate ~e in0 in1 in2 in3 in4 in5 in6 in7 out0 out1 out2 out3 out4 out5 out6 out7 vdd vss
xx1 e0 in0 ~e0 out0 vdd vss transmission_gate
xx2 e0 in1 ~e0 out1 vdd vss transmission_gate
xx3 e0 in2 ~e0 out2 vdd vss transmission_gate
xx4 e0 in3 ~e0 out3 vdd vss transmission_gate
xx5 e1 in4 ~e1 out4 vdd vss transmission_gate
xx6 e1 in5 ~e1 out5 vdd vss transmission_gate
xx7 e1 in6 ~e1 out6 vdd vss transmission_gate
xx8 e1 in7 ~e1 out7 vdd vss transmission_gate
xx9 ~e n001 vss vdd not
xx12 n001 e0 vss vdd buffer
xx10 n001 ~e0 vss vdd not
xx11 n001 ~e1 vss vdd not
xx13 n001 e1 vss vdd buffer
.ends 8_bit_transmission_gate
