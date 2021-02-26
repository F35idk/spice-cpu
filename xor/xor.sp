* C:\users\f35\My Documents\LTspiceXVII\cmos\xor_test_2.asc
m:x1:x2:1 x1:n002 n002 n001 n001 fds4885c_p
m:x1:x2:2 x1:n002 n002 x1:x2:n001 x1:x2:n001 si4820dy
m:x1:x2:3 x1:n002 n004 n001 n001 fds4885c_p
m:x1:x2:4 x1:x2:n001 n004 0 0 si4820dy
m:x1:x1:x1:1 x1:x1:n001 n002 0 0 si4820dy
m:x1:x1:x1:2 x1:x1:n001 n004 x1:x1:x1:n001 x1:x1:x1:n001 fds4885c_p
m:x1:x1:x1:3 x1:x1:x1:n001 n002 n001 n001 fds4885c_p
m:x1:x1:x1:4 x1:x1:n001 n004 0 0 si4820dy
r:x1:x1:x1:shunt x1:x1:x1:n001 0 1e12
m:x1:x1:x2:1 x1:n001 x1:x1:n001 0 0 si4820dy
m:x1:x1:x2:2 x1:n001 x1:x1:n001 n001 n001 fds4885c_p
m:x1:x3:x1:1 x1:x3:n001 x1:n001 n001 n001 fds4885c_p
m:x1:x3:x1:2 x1:x3:n001 x1:n001 x1:x3:x1:n001 x1:x3:x1:n001 si4820dy
m:x1:x3:x1:3 x1:x3:n001 x1:n002 n001 n001 fds4885c_p
m:x1:x3:x1:4 x1:x3:x1:n001 x1:n002 0 0 si4820dy
m:x1:x3:x2:1 nout x1:x3:n001 0 0 si4820dy
m:x1:x3:x2:2 nout x1:x3:n001 n001 n001 fds4885c_p
v1 n001 0 5
r1 nout 0 1k
vb n004 0 5
va n002 0 5
.model si4820dy vdmos(rg=3 rd=8m rs=6m vto=2 kp=70 cgdmax=.8n cgdmin=.1n cgs=1.3n cjo=.4n is=40p rb=10m ksubthres=.1 mfg=siliconix vds=30 ron=20m qg=20n)
.model fds4885c_p vdmos(pchan rg=2.5 vto=-2 rd=12.4m rs=3.1m rb=16m kp=19 lambda=.05 cgdmax=1.2n cgdmin=.2n cgs=1.7n cjo=.5n is=58p ksubthres=.1 mfg=fairchild vds=-40 ron=31m qg=29n)
.tran 1ns 100ns
.end
