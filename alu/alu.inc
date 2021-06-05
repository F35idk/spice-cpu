* alu subcircuit

.include ../8_bit_and/8_bit_and.inc
.include ../8_bit_xor/8_bit_xor.inc
.include ../8_bit_adder/8_bit_adder.inc
.include ../8_bit_mux/8_bit_mux.inc
.include ../8_way_nor/8_way_nor.inc
.include ../tri_state_buffer/tri_state_buffer.inc

.subckt 8_bit_tri_state_buffer ~e in0 in1 in2 in3 in4 in5 in6 in7 out0 out1 out2 out3 out4 out5 out6 out7 vdd vss
xx9 ~e e3 vss vdd not
xx1 in0 out0 vss vdd e3 tri_state_buffer
xx2 in1 out1 vss vdd e3 tri_state_buffer
xx3 in2 out2 vss vdd e3 tri_state_buffer
xx4 in3 out3 vss vdd e3 tri_state_buffer
xx5 in4 out4 vss vdd e7 tri_state_buffer
xx6 in5 out5 vss vdd e7 tri_state_buffer
xx7 in6 out6 vss vdd e7 tri_state_buffer
xx8 in7 out7 vss vdd e7 tri_state_buffer
xx10 ~e e7 vss vdd not
.ends 8_bit_tri_state_buffer

.subckt alu cin f nout nx ny x0 x1 x2 x3 x4 x5 x6 x7 y0 y1 y2 y3 y4 y5 y6 y7 cout q0 q1 q2 q3 q4 q5 q6 q7 vdd vss zr ~oe
xx2 nx nx nx nx nx nx nx nx x0 x1 x2 x3 x4 x5 x6 x7 n001 n002 n003 n004 n005 n006 n007 n008 vss vdd 8_bit_xor
xx5 n014 n016 n019 n022 n024 n026 n028 n031 n001 n002 n003 n004 n005 n006 n007 n008 cout n040 n042 n044 n045 n046 n047 n048 n038 vdd vss cin 8_bit_adder
xx6 n001 n002 n003 n004 n005 n006 n007 n008 n014 n016 n019 n022 n024 n026 n028 n031 n009 n010 n011 n012 n013 n015 n017 n020 vss vdd 8_bit_and
xx7 n009 n010 n011 n012 n013 n015 n017 n020 n038 n040 n042 n044 n045 n046 n047 n048 f n029 n032 n034 n036 n037 n039 n041 n043 vdd vss 8_bit_mux
xx8 nout nout nout nout nout nout nout nout n029 n032 n034 n036 n037 n039 n041 n043 n018 n021 n023 n025 n027 n030 n033 n035 vss vdd 8_bit_xor
xx11 n018 n021 n023 n025 n027 n030 n033 n035 zr vdd vss 8_way_nor
xx4 ny ny ny ny ny ny ny ny y0 y1 y2 y3 y4 y5 y6 y7 n014 n016 n019 n022 n024 n026 n028 n031 vss vdd 8_bit_xor
xx9 ~oe n018 n021 n023 n025 n027 n030 n033 n035 q0 q1 q2 q3 q4 q5 q6 q7 vdd vss 8_bit_tri_state_buffer
.ends alu
