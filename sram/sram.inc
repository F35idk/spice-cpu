* 16 byte sram subcircuit

.incluce ../device_models.inc
.include ../not/not.inc
.include ../buffer/buffer.inc
.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../sr_latch/sr_latch.inc
.include ../edge_detector/edge_detector.inc
.include ../4_to_16_decoder/4_to_16_decoder.inc

.subckt 1_to_4_not in out0 out1 out2 out3 vss vdd
xx1 in out0 vss vdd not
xx2 in out1 vss vdd not
xx3 in out2 vss vdd not
xx4 in out3 vss vdd not
.ends 1_to_4_not

.subckt 1_to_4_buffer in out0 out1 out2 out3 vss vdd
xx1 in out0 vss vdd buffer
xx2 in out1 vss vdd buffer
xx3 in out2 vss vdd buffer
xx4 in out3 vss vdd buffer
.ends 1_to_4_buffer

.subckt transmission_gate e in ~e out vdd vss
xx1 out ~e in vdd pmos_4t
xx2 in e out vss nmos_4t
.ends transmission_gate

.subckt 1_bit_sram_cell_2 r w ~r ~w d vdd vss
xx1 n003 n004 n005 n002 vdd vss sr_latch
xx2 n001 ~w vdd vss n003 nor
xx3 ~w n006 vdd vss n004 nor
xx7 w n001 ~w d vdd vss transmission_gate
xx6 r d ~r n002 vdd vss transmission_gate
r1 n005 vss 400k
xx4 n001 n006 vss vdd not
c1 vss n002 1n
.ends 1_bit_sram_cell_2

.subckt 8_bit_sram_cell ~r ~w d0 d1 d2 d3 d4 d5 d6 d7 vdd vss
xx19 ~r n004 vss vdd not
xx23 n003 r_2 vss vdd not
xx25 n003 r_3 vss vdd not
xx24 n003 r_4 vss vdd not
xx26 n003 r_1 vss vdd not
xx18 n004 ~r_2 vss vdd not
xx20 n004 ~r_3 vss vdd not
xx21 n004 ~r_4 vss vdd not
xx22 n004 ~r_1 vss vdd not
xx17 ~r n003 vss vdd buffer
xx9 ~w n002 vss vdd not
xx10 n001 w_2 vss vdd not
xx11 n001 w_3 vss vdd not
xx12 n001 w_4 vss vdd not
xx13 n001 w_1 vss vdd not
xx14 n002 ~w_2 vss vdd not
xx15 n002 ~w_3 vss vdd not
xx16 n002 ~w_4 vss vdd not
xx27 n002 ~w_1 vss vdd not
xx28 ~w n001 vss vdd buffer
xx1 r_1 w_1 ~r_1 ~w_1 d0 vdd vss 1_bit_sram_cell_2
xx2 r_1 w_1 ~r_1 ~w_1 d1 vdd vss 1_bit_sram_cell_2
xx3 r_2 w_2 ~r_2 ~w_2 d2 vdd vss 1_bit_sram_cell_2
xx4 r_2 w_2 ~r_2 ~w_2 d3 vdd vss 1_bit_sram_cell_2
xx5 r_3 w_3 ~r_3 ~w_3 d4 vdd vss 1_bit_sram_cell_2
xx6 r_3 w_3 ~r_3 ~w_3 d5 vdd vss 1_bit_sram_cell_2
xx7 r_4 w_4 ~r_4 ~w_4 d6 vdd vss 1_bit_sram_cell_2
xx8 r_4 w_4 ~r_4 ~w_4 d7 vdd vss 1_bit_sram_cell_2
.ends 8_bit_sram_cell

.subckt sram a0 a1 a2 a3 clk cs we d0 d1 d2 d3 d4 d5 d6 d7 vdd vss
xx1 a0 a1 a2 a3 sel0 sel1 sel10 sel11 sel12 sel13 sel14 sel15 sel2 sel3 sel4 sel5 sel6 sel7 sel8 sel9 vdd vss 4_to_16_decoder
xx2 n001 n005 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx3 sel0 we3 vdd vss n005 nand
xx4 sel0 cs3 vdd vss n001 nand
xx6 we n018 vdd vss n017 nand
xx7 n017 we3 we7 we11 we15 vss vdd 1_to_4_not
xx8 n009 n013 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx9 sel1 we3 vdd vss n013 nand
xx10 sel1 cs3 vdd vss n009 nand
xx11 n019 n023 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx12 sel2 we3 vdd vss n023 nand
xx13 sel2 cs3 vdd vss n019 nand
xx14 cs cs3 cs7 cs11 cs15 vss vdd 1_to_4_buffer
xx15 n027 n031 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx16 sel3 we3 vdd vss n031 nand
xx17 sel3 cs3 vdd vss n027 nand
xx18 n002 n006 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx19 sel4 we7 vdd vss n006 nand
xx20 sel4 cs7 vdd vss n002 nand
xx21 n010 n014 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx22 sel5 we7 vdd vss n014 nand
xx23 sel5 cs7 vdd vss n010 nand
xx24 n020 n024 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx25 sel6 we7 vdd vss n024 nand
xx26 sel6 cs7 vdd vss n020 nand
xx27 n028 n032 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx28 sel7 we7 vdd vss n032 nand
xx29 sel7 cs7 vdd vss n028 nand
xx30 n003 n007 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx31 sel8 we11 vdd vss n007 nand
xx32 sel8 cs11 vdd vss n003 nand
xx33 n011 n015 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx34 sel9 we11 vdd vss n015 nand
xx35 sel9 cs11 vdd vss n011 nand
xx36 n021 n025 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx37 sel10 we11 vdd vss n025 nand
xx38 sel10 cs11 vdd vss n021 nand
xx39 n029 n033 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx40 sel11 we11 vdd vss n033 nand
xx41 sel11 cs11 vdd vss n029 nand
xx42 n004 n008 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx43 sel12 we15 vdd vss n008 nand
xx44 sel12 cs15 vdd vss n004 nand
xx45 n012 n016 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx46 sel13 we15 vdd vss n016 nand
xx47 sel13 cs15 vdd vss n012 nand
xx48 n022 n026 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx49 sel14 we15 vdd vss n026 nand
xx50 sel14 cs15 vdd vss n022 nand
xx51 n030 n034 d0 d1 d2 d3 d4 d5 d6 d7 vdd vss 8_bit_sram_cell
xx52 sel15 we15 vdd vss n034 nand
xx53 sel15 cs15 vdd vss n030 nand
xx5 clk n018 vdd vss edge_detector
.ends sram
