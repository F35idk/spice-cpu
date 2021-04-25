* alu subcircuit

.include ../8_bit_and/8_bit_and.inc
.include ../8_bit_xor/8_bit_xor.inc
.include ../8_bit_adder/8_bit_adder.inc
.include ../8_bit_mux/8_bit_mux.inc
.include ../8_way_nor/8_way_nor.inc

* block symbol definitions
.subckt alu cin f nout nx ny x0 x1 x2 x3 x4 x5 x6 x7 y0 y1 y2 y3 y4 y5 y6 y7 ~zx ~zy cout out0 out1 out2 out3 out4 out5 out6 out7 vdd vss zr
xx1 ~zx ~zx ~zx ~zx ~zx ~zx ~zx ~zx x0 x1 x2 x3 x4 x5 x6 x7 n006 n008 n010 n012 n014 n016 n018 n020 vss vdd 8_bit_and
xx2 nx nx nx nx nx nx nx nx n006 n008 n010 n012 n014 n016 n018 n020 n001 n002 n003 n004 n005 n007 n009 n011 vss vdd 8_bit_xor
xx3 ~zy ~zy ~zy ~zy ~zy ~zy ~zy ~zy y0 y1 y2 y3 y4 y5 y6 y7 n033 n036 n038 n040 n042 n045 n048 n051 vss vdd 8_bit_and
xx5 n022 n024 n026 n028 n029 n030 n031 n034 n001 n002 n003 n004 n005 n007 n009 n011 cout n046 n049 n052 n053 n054 n055 n056 n043 vdd vss cin 8_bit_adder
xx6 n001 n002 n003 n004 n005 n007 n009 n011 n022 n024 n026 n028 n029 n030 n031 n034 n013 n015 n017 n019 n021 n023 n025 n027 vss vdd 8_bit_and
xx7 n013 n015 n017 n019 n021 n023 n025 n027 n043 n046 n049 n052 n053 n054 n055 n056 f n032 n035 n037 n039 n041 n044 n047 n050 vdd vss 8_bit_mux
xx8 nout nout nout nout nout nout nout nout n032 n035 n037 n039 n041 n044 n047 n050 out0 out1 out2 out3 out4 out5 out6 out7 vss vdd 8_bit_xor
xx11 out0 out1 out2 out3 out4 out5 out6 out7 zr vdd vss 8_way_nor
xx4 ny ny ny ny ny ny ny ny n033 n036 n038 n040 n042 n045 n048 n051 n022 n024 n026 n028 n029 n030 n031 n034 vss vdd 8_bit_xor
.ends alu
