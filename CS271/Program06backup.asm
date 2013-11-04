TITLE Program06     (Program06.asm)

; Author: 	Geoffrey Corey
; Course / Project ID  CS271  Program06               Date: 	3-6-12
; Description:

INCLUDE Irvine32.inc

FRAME macro  				
		push 	ebp
		mov  	ebp, esp
ENDM

getString macro addr_string, len_string	
	LOCAL prompt
	 .data
	 prompt 	BYTE 	10,13,"  Integer: ",0
	 
	 .code
	 mov  	edx, OFFSET prompt
	 call 	WriteString
	 mov  	edx, addr_string
	 mov  	ecx, len_string
	 call 	ReadString
ENDM


MAX = 10
MAX_STRING EQU <"10">
DLIM EQU <"429496729">
DLIM_ = 429496729
DLEN = 10
TRUE = 1
FALSE = 0

.data

; Strings

rule1 		BYTE 	10,13,"This program will get ",MAX_STRING," numbers from the user, validate",\
					" the input,",10,13,"display the numbers, display the sum, and finally display",\
					" the average.",10,13,10,13,10,13,10,13,"Please type an integer within the range ",\
					"[0 .. ",DLIM,"]",10,13,\
					"(It will only read the first 9 digits entered)",10,13,0

error1 		BYTE 	10,13,"You did not inter a valid integer. Please try again.",10,13,0

; Data

array_num		DWORD 	MAX  	DUP(0)
arr_inp 		BYTE 	DLEN 	DUP(0)

valid   		DWORD 	FALSE
number  		DWORD 	?


.code
main 		 PROC	

; introduction(string rule)
	push 	OFFSET rule1
	call 	introduction

get_loop:	
; ReadVal(string in, int length, string prompt)
	push 	OFFSET arr_inp
	push 	LENGTHOF arr_inp
	call 	ReadVal
	
; validate(string in, int length, string error, int valid)
	push 	OFFSET arr_inp
	push 	LENGTHOF arr_inp
	push 	OFFSET error1
	push 	OFFSET valid
	call 	validate
	
	mov  	eax, valid
	cmp  	eax, TRUE
	jne  	get_loop
	
get_done:
; conversion(string in, int length, int number), returns the number on the stack	
	push 	OFFSET arr_inp
	push 	LENGTHOF arr_inp
	call 	conversion
	
	pop  	number


	exit
main 		ENDP

introduction 	PROC 	USES edx
	FRAME
	
	mov  	edx, [ebp+12]
	call 	WriteString
	
	pop  	ebp
	ret 	4
introduction 	ENDP


ReadVal 		PROC 	USES edx ecx

	FRAME

	getString [ebp+20], [ebp+16]	
	
	pop  	ebp
	ret  	8 	
ReadVal 		ENDP

; validate(string in, int length, string error, int valid)
validate 		PROC 	USES 	esi ecx edi eax
LOCAL 			lim:DWORD
	mov  	lim, 429496729
	mov  	esi, [ebp+20]
	mov  	ecx, [ebp+16]
	cld
	
counter:
	lodsb
	
; 	if (char == 0), got to charNull
	cmp  	al, 1
	jl   	charNull
	
; 	if (char >= "0") then continue
	cmp  	al, "0"
	jb   	notDigit
	
; 	if (char <= "9") then continue
	cmp  	al, "9"
	ja   	notDigit	
	loop 	counter
	
notDigit:
; 	Prints out an error message
	mov  	edx, [ebp+12]
	call 	WriteString
	jmp  	val_quit
	
charNull:
	push  	eax 	;save spcae for returning number
	push 	[ebp+20]
	push 	[ebp+16]
	call 	conversion
	
	pop  	eax
	cmp  	eax, 429496729
	jg   	notDigit
	
	mov  	eax, [ebp+8]
	mov  	ebx, TRUE
	mov  	[eax],ebx
	
val_quit:
;	pop  	ebp
	ret  	12
validate 		ENDP

conversion   	PROC 	USES esi ecx edx eax

	FRAME
	
	mov  	esi, [ebp+28]
	mov  	ecx, [ebp+24]
	xor  	edx, edx
	xor  	eax, eax
	cld
conv_alg:
	lodsb
	cmp  	eax, 0
	je   	conv_done
	imul  	edx, edx, 10
	sub  	eax, "0"
	add  	edx, eax
	loop 	conv_alg

conv_done:
	mov  	[ebp+28], edx
	pop  	ebp
	ret  	4
conversion  	ENDP



END main
