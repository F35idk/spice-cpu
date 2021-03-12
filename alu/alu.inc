* alu subcircuit

.include ../8bitand/8bitand.inc
.include ../8bitxor/8bitxor.inc
.include ../8bitadder/8bitadder.inc
.include ../8bitmux/8bitmux.inc
.include ../8waynor/8waynor.inc

.subckt alu cin f nout nx ny x0 x1 x2 x3 x4 x5 x6 x7 y0 y1 y2 y3 y4 y5 y6 y7 zx zy cout out0 out1 out2 out3 out4 out5 out6 out7 vdd vss zr
xx1 n001 n001 n001 n001 n001 n001 n001 n001 x0 x1 x2 x3 x4 x5 x6 x7 n006 n007 n009 n011 n016 n018 n020 n021 vss vdd 8bitand
xx2 nx nx nx nx nx nx nx nx n006 n007 n009 n011 n016 n018 n020 n021 n002 n003 n004 n005 n008 n010 n012 n014 vss vdd 8bitxor
xx3 n026 n026 n026 n026 n026 n026 n026 n026 y0 y1 y2 y3 y4 y5 y6 y7 n033 n036 n039 n041 n043 n046 n049 n052 vss vdd 8bitand
xx4 ny ny ny ny ny ny ny ny n033 n036 n039 n041 n043 n046 n049 n052 n022 n024 n027 n029 n031 n032 n034 n037 vss vdd 8bitxor
xx5 n022 n024 n027 n029 n031 n032 n034 n037 n002 n003 n004 n005 n008 n010 n012 n014 cout n047 n050 n053 n055 n056 n057 n058 n044 vdd vss cin 8bitadder
xx6 n002 n003 n004 n005 n008 n010 n012 n014 n022 n024 n027 n029 n031 n032 n034 n037 n013 n015 n017 n019 n023 n025 n028 n030 vss vdd 8bitand
xx7 n013 n015 n017 n019 n023 n025 n028 n030 n044 n047 n050 n053 n055 n056 n057 n058 f n035 n038 n040 n042 n045 n048 n051 n054 vdd vss 8bitmux
xx8 nout nout nout nout nout nout nout nout n035 n038 n040 n042 n045 n048 n051 n054 out0 out1 out2 out3 out4 out5 out6 out7 vss vdd 8bitxor
xx9 zx n001 vss vdd not
xx10 zy n026 vss vdd not
xx11 out0 out1 out2 out3 out4 out5 out6 out7 zr vdd vss 8waynor
.ends alu
