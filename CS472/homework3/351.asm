pal: 	MOV 	r0, #0x0
again: 	LDRB 	r3, [r1]
 	LDRB 	r4, [r2]
 	CMP 	r3, r4
 	BNE 	notpal
	
 	CMP 	r1, r2
 	BEQ	waspal
 	ADD 	r1, r1, #1
 	SUB 	r2, r2, #1
 	B 	again

waspal: 	MOV 	r0, #0x01
notpal: 	MOV 	pc, lr
