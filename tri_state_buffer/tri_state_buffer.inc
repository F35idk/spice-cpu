* tri-state buffer subcircuit

.include ../nand/nand.inc
.include ../nor/nor.inc
.include ../not/not.inc

.model si4820dy vdmos(rg=3 rd=8m rs=6m vto=2 kp=70 cgdmax=.8n cgdmin=.1n cgs=1.3n cjo=.4n is=40p rb=10m ksubthres=.1 mfg=siliconix vds=30 ron=20m qg=20n)
.model fds4885c_p vdmos(pchan rg=2.5 vto=-2 rd=12.4m rs=3.1m rb=16m kp=19 lambda=.05 cgdmax=1.2n cgdmin=.2n cgs=1.7n cjo=.5n is=58p ksubthres=.1 mfg=fairchild vds=-40 ron=31m qg=29n)

.subckt tri_state_buffer in out vss vdd e
m3 out n001 vdd vdd fds4885c_p
m4 out n002 vss vss si4820dy
xx1 in e vdd vss n001 nand
xx2 in n003 vdd vss n002 nor
xx3 e n003 vss vdd not
.ends tri_state_buffer
