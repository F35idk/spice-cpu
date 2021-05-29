* 2-bit counter test circuit

.include 2_bit_counter.inc

xx1 n004 n002 nq0 nq1 n001 0 2_bit_counter
v1 n001 0 5
v~clk n004 0 5
v~rst n002 0 5
r1 nq1 0 100k
r2 nq0 0 100k

.tran 10ns 100us
.end
