* buffer circuit

.include ../not/not.inc

.subckt buffer in out vss vdd
xx3 in n001 vss vdd not
xx1 n001 out vss vdd not
.ends buffer
