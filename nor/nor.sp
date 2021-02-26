* C:\users\f35\My Documents\LTspiceXVII\cmos\nor_test.asc
r1 nout 0 1k
v1 n001 0 5
m:x1:1 nout n002 0 0 si4820dy
m:x1:2 nout n004 x1:n001 x1:n001 fds4885c_p
m:x1:3 x1:n001 n002 n001 n001 fds4885c_p
m:x1:4 nout n004 0 0 si4820dy
r:x1:shunt x1:n001 0 1e12
va n002 0 0
vb n004 0 0
.model si4820dy vdmos(rg=3 rd=8m rs=6m vto=2 kp=70 cgdmax=.8n cgdmin=.1n cgs=1.3n cjo=.4n is=40p rb=10m ksubthres=.1 mfg=siliconix vds=30 ron=20m qg=20n)
.model fds4885c_p vdmos(pchan rg=2.5 vto=-2 rd=12.4m rs=3.1m rb=16m kp=19 lambda=.05 cgdmax=1.2n cgdmin=.2n cgs=1.7n cjo=.5n is=58p ksubthres=.1 mfg=fairchild vds=-40 ron=31m qg=29n)
.tran 1ns 100ns
.end
