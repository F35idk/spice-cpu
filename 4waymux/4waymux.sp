* C:\users\f35\My Documents\LTspiceXVII\cmos\4waymux_test.asc
v1 n001 0 5
r2 nout 0 1k
va n004 0 0
vsel1 n002 0 0
vsel0 n003 0 0
vb n005 0 0
vc n007 0 0
vd n008 0 0
m:x1:x1:x1:x1:1 x1:x1:x1:n001 x1:x1:n001 0 0 si4820dy
m:x1:x1:x1:x1:2 x1:x1:x1:n001 x1:x1:n002 x1:x1:x1:x1:n001 x1:x1:x1:x1:n001 fds4885c_p
m:x1:x1:x1:x1:3 x1:x1:x1:x1:n001 x1:x1:n001 n001 n001 fds4885c_p
m:x1:x1:x1:x1:4 x1:x1:x1:n001 x1:x1:n002 0 0 si4820dy
r:x1:x1:x1:x1:shunt x1:x1:x1:x1:n001 0 1e12
m:x1:x1:x1:x2:1 x1:n001 x1:x1:x1:n001 0 0 si4820dy
m:x1:x1:x1:x2:2 x1:n001 x1:x1:x1:n001 n001 n001 fds4885c_p
m:x1:x1:x2:x1:1 x1:x1:x2:n001 n004 n001 n001 fds4885c_p
m:x1:x1:x2:x1:2 x1:x1:x2:n001 n004 x1:x1:x2:x1:n001 x1:x1:x2:x1:n001 si4820dy
m:x1:x1:x2:x1:3 x1:x1:x2:n001 x1:x1:n003 n001 n001 fds4885c_p
m:x1:x1:x2:x1:4 x1:x1:x2:x1:n001 x1:x1:n003 0 0 si4820dy
m:x1:x1:x2:x2:1 x1:x1:n002 x1:x1:x2:n001 0 0 si4820dy
m:x1:x1:x2:x2:2 x1:x1:n002 x1:x1:x2:n001 n001 n001 fds4885c_p
m:x1:x1:x3:1 x1:x1:n003 n003 0 0 si4820dy
m:x1:x1:x3:2 x1:x1:n003 n003 n001 n001 fds4885c_p
m:x1:x1:x4:x1:1 x1:x1:x4:n001 n005 n001 n001 fds4885c_p
m:x1:x1:x4:x1:2 x1:x1:x4:n001 n005 x1:x1:x4:x1:n001 x1:x1:x4:x1:n001 si4820dy
m:x1:x1:x4:x1:3 x1:x1:x4:n001 n003 n001 n001 fds4885c_p
m:x1:x1:x4:x1:4 x1:x1:x4:x1:n001 n003 0 0 si4820dy
m:x1:x1:x4:x2:1 x1:x1:n001 x1:x1:x4:n001 0 0 si4820dy
m:x1:x1:x4:x2:2 x1:x1:n001 x1:x1:x4:n001 n001 n001 fds4885c_p
m:x1:x2:x1:x1:1 x1:x2:x1:n001 x1:x2:n001 0 0 si4820dy
m:x1:x2:x1:x1:2 x1:x2:x1:n001 x1:x2:n002 x1:x2:x1:x1:n001 x1:x2:x1:x1:n001 fds4885c_p
m:x1:x2:x1:x1:3 x1:x2:x1:x1:n001 x1:x2:n001 n001 n001 fds4885c_p
m:x1:x2:x1:x1:4 x1:x2:x1:n001 x1:x2:n002 0 0 si4820dy
r:x1:x2:x1:x1:shunt x1:x2:x1:x1:n001 0 1e12
m:x1:x2:x1:x2:1 x1:n002 x1:x2:x1:n001 0 0 si4820dy
m:x1:x2:x1:x2:2 x1:n002 x1:x2:x1:n001 n001 n001 fds4885c_p
m:x1:x2:x2:x1:1 x1:x2:x2:n001 n007 n001 n001 fds4885c_p
m:x1:x2:x2:x1:2 x1:x2:x2:n001 n007 x1:x2:x2:x1:n001 x1:x2:x2:x1:n001 si4820dy
m:x1:x2:x2:x1:3 x1:x2:x2:n001 x1:x2:n003 n001 n001 fds4885c_p
m:x1:x2:x2:x1:4 x1:x2:x2:x1:n001 x1:x2:n003 0 0 si4820dy
m:x1:x2:x2:x2:1 x1:x2:n002 x1:x2:x2:n001 0 0 si4820dy
m:x1:x2:x2:x2:2 x1:x2:n002 x1:x2:x2:n001 n001 n001 fds4885c_p
m:x1:x2:x3:1 x1:x2:n003 n003 0 0 si4820dy
m:x1:x2:x3:2 x1:x2:n003 n003 n001 n001 fds4885c_p
m:x1:x2:x4:x1:1 x1:x2:x4:n001 n008 n001 n001 fds4885c_p
m:x1:x2:x4:x1:2 x1:x2:x4:n001 n008 x1:x2:x4:x1:n001 x1:x2:x4:x1:n001 si4820dy
m:x1:x2:x4:x1:3 x1:x2:x4:n001 n003 n001 n001 fds4885c_p
m:x1:x2:x4:x1:4 x1:x2:x4:x1:n001 n003 0 0 si4820dy
m:x1:x2:x4:x2:1 x1:x2:n001 x1:x2:x4:n001 0 0 si4820dy
m:x1:x2:x4:x2:2 x1:x2:n001 x1:x2:x4:n001 n001 n001 fds4885c_p
m:x1:x3:x1:x1:1 x1:x3:x1:n001 x1:x3:n001 0 0 si4820dy
m:x1:x3:x1:x1:2 x1:x3:x1:n001 x1:x3:n002 x1:x3:x1:x1:n001 x1:x3:x1:x1:n001 fds4885c_p
m:x1:x3:x1:x1:3 x1:x3:x1:x1:n001 x1:x3:n001 n001 n001 fds4885c_p
m:x1:x3:x1:x1:4 x1:x3:x1:n001 x1:x3:n002 0 0 si4820dy
r:x1:x3:x1:x1:shunt x1:x3:x1:x1:n001 0 1e12
m:x1:x3:x1:x2:1 nout x1:x3:x1:n001 0 0 si4820dy
m:x1:x3:x1:x2:2 nout x1:x3:x1:n001 n001 n001 fds4885c_p
m:x1:x3:x2:x1:1 x1:x3:x2:n001 x1:n001 n001 n001 fds4885c_p
m:x1:x3:x2:x1:2 x1:x3:x2:n001 x1:n001 x1:x3:x2:x1:n001 x1:x3:x2:x1:n001 si4820dy
m:x1:x3:x2:x1:3 x1:x3:x2:n001 x1:x3:n003 n001 n001 fds4885c_p
m:x1:x3:x2:x1:4 x1:x3:x2:x1:n001 x1:x3:n003 0 0 si4820dy
m:x1:x3:x2:x2:1 x1:x3:n002 x1:x3:x2:n001 0 0 si4820dy
m:x1:x3:x2:x2:2 x1:x3:n002 x1:x3:x2:n001 n001 n001 fds4885c_p
m:x1:x3:x3:1 x1:x3:n003 n002 0 0 si4820dy
m:x1:x3:x3:2 x1:x3:n003 n002 n001 n001 fds4885c_p
m:x1:x3:x4:x1:1 x1:x3:x4:n001 x1:n002 n001 n001 fds4885c_p
m:x1:x3:x4:x1:2 x1:x3:x4:n001 x1:n002 x1:x3:x4:x1:n001 x1:x3:x4:x1:n001 si4820dy
m:x1:x3:x4:x1:3 x1:x3:x4:n001 n002 n001 n001 fds4885c_p
m:x1:x3:x4:x1:4 x1:x3:x4:x1:n001 n002 0 0 si4820dy
m:x1:x3:x4:x2:1 x1:x3:n001 x1:x3:x4:n001 0 0 si4820dy
m:x1:x3:x4:x2:2 x1:x3:n001 x1:x3:x4:n001 n001 n001 fds4885c_p
.model si4820dy vdmos(rg=3 rd=8m rs=6m vto=2 kp=70 cgdmax=.8n cgdmin=.1n cgs=1.3n cjo=.4n is=40p rb=10m ksubthres=.1 mfg=siliconix vds=30 ron=20m qg=20n)
.model fds4885c_p vdmos(pchan rg=2.5 vto=-2 rd=12.4m rs=3.1m rb=16m kp=19 lambda=.05 cgdmax=1.2n cgdmin=.2n cgs=1.7n cjo=.5n is=58p ksubthres=.1 mfg=fairchild vds=-40 ron=31m qg=29n)
.tran 1ns 100ns
.end
