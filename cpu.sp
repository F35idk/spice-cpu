* cpu test circuit

.include circuits/d_flip_flop/d_flip_flop.inc
.include circuits/alu/alu.inc
.include circuits/sram/sram.inc
.include circuits/rom/rom.inc
.include circuits/program_counter/program_counter.inc
.include circuits/mux/mux.inc
.include circuits/nor/nor.inc
.include circuits/8_bit_register/8_bit_register.inc
.include circuits/control_unit/control_unit.inc
.include circuits/power_on_reset_circuit/power_on_reset_circuit.inc

* 2-bit d flip-flop used as a flags register
.subckt 2_bit_d_flip_flop clk d0 d1 q0 q1 vdd vss ~q0 ~q1 ie rst
xx1 n001 ~d0 q0 ~q0 vdd vss d_flip_flop
xx2 n001 ~d1 q1 ~q1 vdd vss d_flip_flop
xx3 clk n003 vdd vss n002 clock_gate
xx4 n002 n001 vss vdd not
xx6 n004 d1 vdd vss ~d1 nand
xx7 rst n004 vss vdd not
xx5 d0 n004 vdd vss ~d0 nand
xx8 rst ie n003 vdd vss or
.ends 2_bit_d_flip_flop

* 4-bit d flip-flop used as a memory address register
.subckt 4_bit_d_flip_flop clk d0 d1 d2 d3 ie q0 q1 q2 q3 vdd vss
r1 n001 vss 100k
r2 n004 vss 100k
r3 n005 vss 100k
r4 n007 vss 100k
xx5 n003 n006 vss vdd not
xx6 n003 n002 vss vdd not
xx1 n002 d0 n001 q0 vdd vss d_flip_flop
xx2 n002 d1 n004 q1 vdd vss d_flip_flop
xx3 n006 d2 n005 q2 vdd vss d_flip_flop
xx4 n006 d3 n007 q3 vdd vss d_flip_flop
xx7 clk ie vdd vss n003 clock_gate
.ends 4_bit_d_flip_flop

xx3 nmar0 nmar1 nmar2 nmar3 ram_out ~ram_in nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 vdd 0 sram
xxrom nmar0 nmar1 nmar2 nmar3 ~rom_out nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 vdd 0 rom
rd0 0 nd0 50k
rd1 0 nd1 50k
rd2 0 nd2 50k
rd3 0 nd3 50k
rd4 0 nd4 50k
rd5 0 nd5 50k
rd6 0 nd6 50k
rd7 0 nd7 50k
xx8 clk n023 n024 carry_flag zero_flag vdd 0 n022 n034 flags_in reset 2_bit_d_flip_flop
xx10 ~carry n022 vdd 0 n021 nor
r1 0 n034 100k
vclk clk 0 pulse(0 5 2u 0 0 2u 4u)
vsource vdd 0 0
rx0 0 nx0 200k
rx1 0 nx1 200k
rx2 0 nx2 200k
rx3 0 nx3 200k
rx4 0 nx4 200k
rx5 0 nx5 200k
rx6 0 nx6 200k
rx7 0 nx7 200k
r3 nd0 0 50k
r4 nd6 0 50k
r5 nd7 0 50k
r6 nd5 0 50k
r7 nd4 0 50k
r8 nd3 0 50k
r9 nd2 0 50k
r10 nd1 0 50k
xx6 clk nd0 nd1 nd2 nd3 mar_in nmar0 nmar1 nmar2 nmar3 vdd 0 4_bit_d_flip_flop
rmar0 0 nmar0 200k
rmar1 0 nmar1 200k
rmar2 0 nmar2 200k
rmar3 0 nmar3 200k
xx5 clk x_in ~x_out nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 nx0 nx1 nx2 nx3 nx4 nx5 nx6 nx7 vdd 0 8_bit_register
xx9 clk y_in ~y_out nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 ny0 ny1 ny2 ny3 ny4 ny5 ny6 ny7 vdd 0 8_bit_register
xx11 clk ir_in ~ir_out nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 nir0 nir1 nir2 nir3 nir4 nir5 nir6 nir7 vdd 0 8_bit_register
rir1 0 nir1 200k
rir2 0 nir2 200k
rir3 0 nir3 200k
rir0 0 nir0 200k
xx15 pc_in n046 n045 vdd 0 or
xx7 carry_flag branch_carry vdd 0 n047 nand
xx12 zero_flag branch_zr vdd 0 n042 nand
xx13 n042 n047 vdd 0 n046 nand
xx2 n021 add not_out not_x not_y nx0 nx1 nx2 nx3 nx4 nx5 nx6 nx7 ny0 ny1 ny2 ny3 ny4 ny5 ny6 ny7 n023 nd0 nd1 nd2 nd3 nd4 nd5 nd6 nd7 vdd 0 n024 ~alu_out alu
xxcu clk nir4 nir5 nir6 nir7 reset ~y_out add branch_zr count_enable flags_in ir_in mar_in not_out not_x not_y pc_in pc_out ram_out vdd 0 x_in y_in ~alu_out ~carry ~ir_out ~ram_in ~rom_out ~x_out branch_carry control_unit
rpc0 0 npc0 200k
rpc1 0 npc1 200k
rpc2 0 npc2 200k
rpc3 0 npc3 200k
xx16 reset vdd 0 power_on_reset_circuit
xx1 clk pc_out count_enable n045 nd0 nd1 nd2 nd3 vdd 0 reset npc0 npc1 npc2 npc3 program_counter
rir4 0 nir4 200k
rir5 0 nir5 200k
rir6 0 nir6 200k
rir7 0 nir7 200k
rdummy 0 n023 200k

.end
