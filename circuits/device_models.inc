.model 1n4148 d(is=2.52n rs=.568 n=1.752 cjo=4p m=.4 tt=20n iave=200m vpk=75 mfg=onsemi)

* 4-terminal pmos subcircuit
.subckt pmos_4t d g s b
c1 d n001 200f
c2 s n001 1p
r1 n001 g 3
m1 d n001 s b pmos_4t_model
.model pmos_4t_model pmos(level=1 vto=-2.0 kp = 70e-4 rd = 1m rs = 1m)
.ends pmos_4t

* 4-terminal nmos subcircuit
.subckt nmos_4t d g s b
m1 d n001 s b nmos_4t_model
c1 d n001 200f
c2 s n001 1p
r1 n001 g 3
.model nmos_4t_model nmos(level=1 vto=2.0 kp = 70e-4 rd = 1m rs = 1m)
.ends nmos_4t
