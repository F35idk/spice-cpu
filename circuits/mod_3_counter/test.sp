* synchronous mod 3 counter test circuit

.include mod_3_counter.inc

v1 n001 0 5
v~clk n004 0 5
vrst n002 0 5
r1 nq1 0 100k
r2 nq0 0 100k
xx1 n004 n002 nq0 nq1 n001 0 mod_3_counter

.tran 10ns 120us
.end
