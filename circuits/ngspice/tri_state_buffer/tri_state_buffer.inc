* tri-state buffer subcircuit

.include ../mosfet/mosfet.inc
.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../not/not.inc

.subckt tri_state_buffer in out vss vdd e
xx1 in e vdd vss n001 nand
xx2 in n003 vdd vss n002 nor
xx3 e n003 vss vdd not
xx4 out n001 vdd vdd pmos_4t
xx5 out n002 vss vss nmos_4t
.ends tri_state_buffer

.subckt tri_state_buffer_shunt in out vss vdd e
xx1 in e vdd vss n001 nand
xx2 in n003 vdd vss n002 nor
xx3 e n003 vss vdd not
xx4 out n001 vdd vdd pmos_4t
xx5 out n002 vss vss nmos_4t
rshunt vdd out 1e5
.ends tri_state_buffer_shunt
