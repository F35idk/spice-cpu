* tri-state buffer subcircuit

.include ../device_models.inc
.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../not/not.inc

.subckt tri_state_buffer in out vss vdd e
m3 out n001 vdd vdd fds4885c_p
m4 out n002 vss vss si4820dy
xx1 in e vdd vss n001 nand
xx2 in n003 vdd vss n002 nor
xx3 e n003 vss vdd not
.ends tri_state_buffer
