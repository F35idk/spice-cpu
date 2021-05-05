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

.subckt alu cin f nout nx ny x0 x1 x2 x3 x4 x5 x6 x7 y0 y1 y2 y3 y4 y5 y6 y7 ~zx ~zy cout q0 q1 q2 q3 q4 q5 q6 q7 vdd vss zr ~oe
xx1 ~zx ~zx ~zx ~zx ~zx ~zx ~zx ~zx x0 x1 x2 x3 x4 x5 x6 x7 n006 n008 n010 n012 n014 n016 n018 n020 vss vdd 8_bit_and
xx2 nx nx nx nx nx nx nx nx n006 n008 n010 n012 n014 n016 n018 n020 n001 n002 n003 n004 n005 n007 n009 n011 vss vdd 8_bit_xor
xx3 ~zy ~zy ~zy ~zy ~zy ~zy ~zy ~zy y0 y1 y2 y3 y4 y5 y6 y7 n039 n043 n046 n048 n050 n053 n056 n059 vss vdd 8_bit_and
xx5 n022 n024 n027 n030 n032 n034 n036 n040 n001 n002 n003 n004 n005 n007 n009 n011 cout n054 n057 n060 n061 n062 n063 n064 n051 vdd vss cin 8_bit_adder
xx6 n001 n002 n003 n004 n005 n007 n009 n011 n022 n024 n027 n030 n032 n034 n036 n040 n013 n015 n017 n019 n021 n023 n025 n028 vss vdd 8_bit_and
xx7 n013 n015 n017 n019 n021 n023 n025 n028 n051 n054 n057 n060 n061 n062 n063 n064 f n037 n041 n044 n047 n049 n052 n055 n058 vdd vss 8_bit_mux
xx8 nout nout nout nout nout nout nout nout n037 n041 n044 n047 n049 n052 n055 n058 n026 n029 n031 n033 n035 n038 n042 n045 vss vdd 8_bit_xor
xx11 n026 n029 n031 n033 n035 n038 n042 n045 zr vdd vss 8_way_nor
xx4 ny ny ny ny ny ny ny ny n039 n043 n046 n048 n050 n053 n056 n059 n022 n024 n027 n030 n032 n034 n036 n040 vss vdd 8_bit_xor
xx9 ~oe n026 n029 n031 n033 n035 n038 n042 n045 q0 q1 q2 q3 q4 q5 q6 q7 vdd vss 8_bit_tri_state_buffer
.ends alu
