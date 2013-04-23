Loop:
	LDR 	r2, [r0], #1
	STR 	r2, [r1], #1
	CMP 	r2, #0 	; reached null, and stored in memory.
	BNE 	Loop
