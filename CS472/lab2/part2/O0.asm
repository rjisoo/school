;## -O0 ##
main:
	push	{r7, lr}
	sub	sp, sp, #24
	add	r7, sp, #0
	movw	r3, #:lower16:__stack_chk_guard
	movt	r3, #:upper16:__stack_chk_guard
	ldr	r3, [r3, #0]
	str	r3, [r7, #20]
	movw	r3, #28525
	movt	r3, 109
	str	r3, [r7, #12]
	add	r3, r7, #12
	mov	r0, r3
	bl	strlen
	mov	r3, r0
	add	r3, r3, #-1
	str	r3, [r7, #0]
	mov	r3, #0
	str	r3, [r7, #4]
	b	.L2
.L3:
	add	r2, r7, #12
	ldr	r3, [r7, #0]
	adds	r3, r2, r3
	ldrb	r2, [r3, #0]	@ zero_extendqisi2
	add	r1, r7, #16
	ldr	r3, [r7, #4]
	adds	r3, r1, r3
	strb	r2, [r3, #0]
	ldr	r3, [r7, #0]
	add	r3, r3, #-1
	str	r3, [r7, #0]
	ldr	r3, [r7, #4]
	add	r3, r3, #1
	str	r3, [r7, #4]
.L2:
	ldr	r3, [r7, #0]
	mvn	r3, r3
	lsr	r3, r3, #31
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L3
	add	r2, r7, #16
	ldr	r3, [r7, #4]
	adds	r3, r2, r3
	mov	r2, #0
	strb	r2, [r3, #0]
	add	r2, r7, #16
	add	r3, r7, #12
	mov	r0, r2
	mov	r1, r3
	bl	strcmp
	mov	r3, r0
	cmp	r3, #0
	beq	.L4
	mov	r3, #0
	str	r3, [r7, #8]
	b	.L5
.L4:
	mov	r3, #1
	str	r3, [r7, #8]
.L5:
	mov	r3, #0
	mov	r0, r3
	movw	r3, #:lower16:__stack_chk_guard
	movt	r3, #:upper16:__stack_chk_guard
	ldr	r2, [r7, #20]
	ldr	r3, [r3, #0]
	cmp	r2, r3
	beq	.L6
	bl	__stack_chk_fail
.L6:
	add	r7, r7, #24
	mov	sp, r7
	pop	{r7, pc}

