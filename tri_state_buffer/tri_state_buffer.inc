* tri-state buffer subcircuit

.include ../device_models.inc
.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../not/not.inc

.subckt tri_state_buffer in out vss vdd e
xx1 in e vdd vss n001 nand
xx2 in n005 vdd vss n003 nor
xx3 e n005 vss vdd not
xx4 out n001 vdd n002 pmos_4t
xx5 out n003 vss n004 nmos_4t
.ends tri_state_buffer
