;## -01 ##
main:
	push	{lr}
	sub	sp, sp, #12
	movw	r3, #:lower16:__stack_chk_guard
	movt	r3, #:upper16:__stack_chk_guard
	ldr	r3, [r3, #0]
	str	r3, [sp, #4]
	movw	r3, #28525
	movt	r3, 109
	add	r0, sp, #8
	str	r3, [r0, #-8]!
	mov	r0, sp
	bl	strlen
	subs	r0, r0, #1
	bmi	.L2
.L5:
	subs	r0, r0, #1
	bpl	.L5
.L2:
	mov	r0, #0
	movw	r3, #:lower16:__stack_chk_guard
	movt	r3, #:upper16:__stack_chk_guard
	ldr	r2, [sp, #4]
	ldr	r3, [r3, #0]
	cmp	r2, r3
	beq	.L4
	bl	__stack_chk_fail
.L4:
	add	sp, sp, #12
	pop	{pc}
