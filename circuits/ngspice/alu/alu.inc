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
xx2 n007 n007 n007 n007 n009 n009 n009 n009 x0 x1 x2 x3 x4 x5 x6 x7 n010 n011 n012 n013 n014 n015 n016 n017 vss vdd 8_bit_xor
xx5 n023 n025 n028 n031 n033 n035 n037 n040 n010 n011 n012 n013 n014 n015 n016 n017 cout n049 n051 n053 n054 n055 n056 n057 n047 vdd vss cin 8_bit_adder
xx6 n010 n011 n012 n013 n014 n015 n016 n017 n023 n025 n028 n031 n033 n035 n037 n040 n018 n019 n020 n021 n022 n024 n026 n029 vss vdd 8_bit_and
xx7 n018 n019 n020 n021 n022 n024 n026 n029 n047 n049 n051 n053 n054 n055 n056 n057 f n038 n041 n043 n045 n046 n048 n050 n052 vdd vss 8_bit_mux
xx8 n004 n004 n004 n004 n008 n008 n008 n008 n038 n041 n043 n045 n046 n048 n050 n052 n027 n030 n032 n034 n036 n039 n042 n044 vss vdd 8_bit_xor
xx11 n027 n030 n032 n034 n036 n039 n042 n044 zr vdd vss 8_way_nor
xx4 n002 n002 n002 n002 n005 n005 n005 n005 y0 y1 y2 y3 y4 y5 y6 y7 n023 n025 n028 n031 n033 n035 n037 n040 vss vdd 8_bit_xor
xx9 ~oe n027 n030 n032 n034 n036 n039 n042 n044 q0 q1 q2 q3 q4 q5 q6 q7 vdd vss 8_bit_tri_state_buffer
xx3 n006 n007 vss vdd not
xx1 n006 n009 vss vdd not
xx10 nx n006 vss vdd not
xx12 n003 n004 vss vdd not
xx13 n003 n008 vss vdd not
xx14 nout n003 vss vdd not
xx15 n001 n002 vss vdd not
xx16 n001 n005 vss vdd not
xx17 ny n001 vss vdd not
.ends alu
