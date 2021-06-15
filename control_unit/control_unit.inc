* control unit subcircuit

.include ../mod_3_counter/mod_3_counter.inc
.include ../and/and.inc
.include ../or/or.inc
.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../not/not.inc
.include ../1_to_4_buffer/1_to_4_buffer.inc

.subckt control_unit clk i4 i5 i6 i7 rst ~y_out add branch_zr count_enable flags_in ir_in mar_in not_out not_x not_y pc_in pc_out ram_out vdd vss x_in y_in ~alu_out ~carry ~ir_out ~ram_in ~rom_out ~x_out branch_carry
xx2 n006 i5 vdd vss n002 and
xxrom2 n001 n002 n003 n004 vss rom_out ~x_in x_out ~y_in y_out ~branch_carry n008 n008 vdd vss rom
xx4 n006 i4 vdd vss n007 and
xx5 n006 i6 vdd vss n003 and
xx6 n006 i7 vdd vss n004 and
xx7 n005 n007 n001 vdd vss or
xx1 clk rst n005 n006 vdd vss mod_3_counter
xxrom1 n001 n002 n003 n004 vss ~mar_in ~not_out ~not_x ~not_y ~pc_in ~pc_out ram_in ~ram_out vdd vss rom
xxrom0 n001 n002 n003 n004 vss alu_out carry ~add ~branch_zr ~count_enable ~flags_in ~ir_in ir_out vdd vss rom
r1 n008 vss 100k
xx10 ~add rst2 vdd vss add nor
xx11 alu_out ~rst3 vdd vss ~alu_out nand
xx12 carry ~rst3 vdd vss ~carry nand
xx13 ~branch_zr rst2 vdd vss branch_zr nor
xx14 ~count_enable rst2 vdd vss count_enable nor
xx15 ~flags_in rst6 vdd vss flags_in nor
xx16 ~ir_in rst6 vdd vss ir_in nor
xx17 ~not_y rst10 vdd vss not_y nor
xx20 ~pc_in rst10 vdd vss pc_in nor
xx21 ~pc_out rst10 vdd vss pc_out nor
xx23 ~ram_out rst13 vdd vss ram_out nor
xx19 ~not_x rst10 vdd vss not_x nor
xx18 ir_out ~rst3 vdd vss ~ir_out nand
xx24 ~not_out rst6 vdd vss not_out nor
xx25 ~mar_in rst6 vdd vss mar_in nor
xx22 ram_in ~rst3 vdd vss ~ram_in nand
xx26 ~y_in rst13 vdd vss y_in nor
xx31 ~x_in rst13 vdd vss x_in nor
xx28 rom_out ~rst6 vdd vss ~rom_out nand
xx29 x_out ~rst6 vdd vss ~x_out nand
xx27 y_out ~rst6 vdd vss ~y_out nand
xx35 rst13 ~rst6 vss vdd not
xx36 rst2 ~rst3 vss vdd not
xx33 rst rst2 rst6 rst10 rst13 vss vdd 1_to_4_buffer
xx3 ~branch_carry rst vdd vss branch_carry nor
.ends control_unit
