* demultiplexer test circuit

.include dmux.inc

v1 n002 0 5
r2 na 0 1k
vin n004 0 0
vsel n001 0 0
xx1 n004 n001 na nb n002 0 dmux
r1 nb 0 1k

.tran 1ns 100ns
.end
