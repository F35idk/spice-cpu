.model si4820dy vdmos(rg=3 rd=8m rs=6m vto=2 kp=70 cgdmax=.8n cgdmin=.1n cgs=1.3n cjo=.4n is=40p rb=10m ksubthres=.1 mfg=siliconix vds=30 ron=20m qg=20n)
.model fds4885c_p vdmos(pchan rg=2.5 vto=-2 rd=12.4m rs=3.1m rb=16m kp=19 lambda=.05 cgdmax=1.2n cgdmin=.2n cgs=1.7n cjo=.5n is=58p ksubthres=.1 mfg=fairchild vds=-40 ron=31m qg=29n)
.model 1n4148 d(is=2.52n rs=.568 n=1.752 cjo=4p m=.4 tt=20n iave=200m vpk=75 mfg=onsemi)

* 4-terminal pmos subcircuit
.subckt pmos_4t d g s b
c1 d n001 200f
c2 s n001 1p
r1 n001 g 3
m1 d n001 s b pmos_4t_model
.model pmos_4t_model pmos(level=1 vto=-2.0 kp = 70e-4 rd = 1m rs = 1m rb = 1m)
.ends pmos_4t

* 4-terminal nmos subcircuit
.subckt nmos_4t d g s b
m1 d n001 s b nmos_4t_model
c1 d n001 200f
c2 s n001 1p
r1 n001 g 3
.model nmos_4t_model nmos(level=1 vto=2.0 kp = 70e-4 rd = 1m rs = 1m rb = 1m)
.ends nmos_4t
