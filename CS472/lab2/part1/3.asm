 	AREA 	LabTwo, CODE, READONLY
 	ENTRY

 	LDR 	r0, A
 	LDR 	r1, B
 	LDR 	r2, C
 	LDR 	r3, D
 	LDR 	r4, E
 	ADD 	r0, r0, r1
 	ADD 	r0, r0, r2
 	MUL 	r5, r3, r4
 	SUB 	r5, r0, r5

A 	DCD 	4
B 	DCD 	12
C 	DCD 	-2
D 	DCD 	2
E 	DCD 	3

 	END
