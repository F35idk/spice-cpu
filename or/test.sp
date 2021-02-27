* c:\users\f35\my documents\ltspicexvii\cmos\or_test.asc

.include or.inc

v1 n001 0 5
r1 nout 0 1k
xx1 n002 n003 nout n001 0 or
vb n003 0 5
va n002 0 0

.tran 1ns 100ns
.end
