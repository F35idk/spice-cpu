* nor gate subcircuit
.subckt nor a b vdd vss out
m1 out a vss vss si4820dy
m2 out b n001 n001 fds4885c_p
m3 n001 a vdd vdd fds4885c_p
m4 out b vss vss si4820dy
rshunt n001 vss 1e12
.ends nor

.model si4820dy vdmos(rg=3 rd=8m rs=6m vto=2 kp=70 cgdmax=.8n cgdmin=.1n cgs=1.3n cjo=.4n is=40p rb=10m ksubthres=.1 mfg=siliconix vds=30 ron=20m qg=20n)
.model fds4885c_p vdmos(pchan rg=2.5 vto=-2 rd=12.4m rs=3.1m rb=16m kp=19 lambda=.05 cgdmax=1.2n cgdmin=.2n cgs=1.7n cjo=.5n is=58p ksubthres=.1 mfg=fairchild vds=-40 ron=31m qg=29n)
