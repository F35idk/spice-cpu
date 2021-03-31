* 4 to 16 decoder test circuit

.include 4_to_16_decoder.inc

xx1 n008 n010 n012 n014 nd0 nd1 nd10 nd11 nd12 nd13 nd14 nd15 nd2 nd3 nd4 nd5 nd6 nd7 nd8 nd9 n001 0 4_to_16_decoder
v1 n001 0 5
va n008 0 5
vb n010 0 5
vc n012 0 5
vd n014 0 5
r1 nd15 0 1k
r2 nd14 0 1k
r3 nd13 0 1k
r4 nd12 0 1k
r5 nd11 0 1k
r6 nd10 0 1k
r7 nd9 0 1k
r8 nd8 0 1k
r9 nd7 0 1k
r10 nd6 0 1k
r11 nd5 0 1k
r12 nd4 0 1k
r13 nd3 0 1k
r14 nd2 0 1k
r15 nd1 0 1k
r16 nd0 0 1k

.tran 1ns 20u
.option rshunt=1e9
.end
