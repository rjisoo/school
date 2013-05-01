 	AREA 	LabTwo, CODE, READONLY
 	ENTRY

 	MOV 	r0, #5
 	MOV 	r1, #2
 	MOV 	r2, #2
 	MOV 	r3, #2
 	MOV 	r4, #3
 	ADD 	r0, r0, r1
 	ADD 	r0, r0, r2
 	MUL 	r5, r3, r4
 	SUB 	r5, r0, r5

 	END
