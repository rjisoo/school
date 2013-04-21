Loop:
	LDR 	r2, [r0], #4
	STR 	r2, [r1], #4
	CMP 	r2, #0 	; reached null, and stored in memory.
	BNE 	Loop
