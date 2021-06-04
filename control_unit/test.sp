* control unit test circuit

.include control_unit.inc

xx1 n015 n001 n002 n003 n004 n017 n~y_out nadd nbranch_zr ncount_enable nflags_in nir_in nmar_in nnot_out nnot_x nnot_y npc_in npc_out nram_out n005 0 nx_in ny_in n~alu_out n~carry n~ir_out n~ram_in n~rom_out n~x_out nbranch_carry control_unit
r1 0 n~y_out 100k
r2 0 ny_in 100k
r3 0 n~x_out 100k
r4 0 nx_in 100k
r5 0 n~rom_out 100k
r6 0 nram_out 100k
r7 0 n~ram_in 100k
r8 0 npc_out 100k
v1 n005 0 5
vi4 n001 0 5
vclk n015 0 5
vrst n017 0 5
vi5 n002 0 5
vi6 n003 0 5
vi7 n004 0 5
r9 0 npc_in 100k
r10 0 nnot_y 100k
r11 0 nnot_x 100k
r12 0 nnot_out 100k
r13 0 nmar_in 100k
r14 0 n~ir_out 100k
r15 0 nir_in 100k
r16 0 nflags_in 100k
r17 0 ncount_enable 100k
r18 0 nbranch_zr 100k
r19 0 nadd 100k
r20 0 n~carry 100k
r21 0 n~alu_out 100k
r22 0 nbranch_carry 100k

.tran 10ns 80u
.end
