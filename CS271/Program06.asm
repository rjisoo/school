TITLE Program06     (Program06.asm)

; Author: 	Geoffrey Corey
; Course / Project ID  CS271  Program06               Date: 	3-6-12
; Description: 	Design and implement method for getting input from a user, checking if it's a number
; 				check if it will fit in a DWORD, and the convert it from a string to an integer, and
; 				then convert an integer into a string. Finally, use these procedures to get 10 numbers
; 				from a user, add them to an array, get the sum, average, and then print the array, the
; 				sum, and the average.

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

displayString macro addr_string
	mov  	edx, addr_string
	call 	WriteString
ENDM


MAX = 10
BASE = 10
MAX_STRING EQU <"10">
DLIM EQU <"429496729">
DLIM_ = 429496729
TRUE = 1
FALSE = 0

.data

; Strings
rule1 		BYTE 	10,13,"This program will get ",MAX_STRING," numbers from the user, validate",\
					" the input,",10,13,"display the numbers, display the sum, and finally display",\
					" the average",10,13,"(rounded down to the nearest integer.",10,13,10,13,10,\
					13,10,13,"Please type an integer within the range [0 .. ",DLIM,"]",10,13,\
					"(It will only read the first 9 digits entered)",10,13,0

error1 		BYTE 	10,13,"You did not inter a valid integer. Please try again.",10,13,0

result1 	BYTE 	10,13,"The entered list is as follows:",10,13,0
result2 	BYTE 	10,13,"The sum is: ",0
result3 	BYTE 	10,13,"The average is: ",0
special 	BYTE 	9,0

; Arrays
array_num		DWORD 	MAX  	DUP(0)
string_out 		BYTE 	MAX 	DUP(?)

; Integers
number  		DWORD 	?
sum 			DWORD 	?
average 		DWORD 	?


.code
main 		 PROC	

; introduction(string rule)	
; readVal(string error), 	returns the read number on the stack
; validate(string in, int length, string error, int valid)
; convertInt(string in, int length), returns the number on the stack
; arrayMath(int array[], int length), returns sum and average on the stack, pop sum first
; convertChar( string out, integer)
; displayArray(int arr[], int length, string special)
; writeVal(int number)


	push 	OFFSET rule1
	call 	introduction
	
	mov  	esi, OFFSET array_num
	mov  	ecx, LENGTHOF array_num
	
loop_array:	
	push 	OFFSET error1
	call 	readVal
	pop  	[esi]
	add  	esi, 4
	loop 	loop_array

	push  	OFFSET array_num
	push 	LENGTHOF array_num
	call 	arrayMath
	
	pop  	sum
	pop 	average

	mov  	edx, OFFSET result1
	call 	WriteString
	
	push 	OFFSET array_num
	push 	LENGTHOF array_num
	push 	OFFSET special
	call 	displayArray

	mov  	edx, OFFSET result2
	call 	WriteString
	
	push 	sum
	call 	WriteVal
	
	call 	Crlf
	
	mov  	edx, OFFSET result3
	call 	WriteString
	push 	average
	call 	WriteVal
	
	call 	Crlf
	call 	Crlf
	
	
	exit
main 		ENDP

; introduction(string rule)	
introduction 	PROC 	USES edx
	FRAME
	
	mov  	edx, [ebp+12]
	call 	WriteString
	
	pop  	ebp
	ret 	4
introduction 	ENDP

; readVal(string error), 	returns the read number on the stack
readVal 		PROC 	USES edx ecx eax ebx esi
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Procedure: 	 readVal
; Description: 	 reads input from a user, then checks if it is a number, and then converts the input to
;				 an integer
; Recieves: 	 addres of an error string
; Returns: 		 DWORD integer on stack
; Preconditions: none
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LOCAL 			user_in[MAX]:BYTE, valid:DWORD

get_loop:
	lea  	eax, user_in
	getString eax, LENGTHOF user_in
	mov  	ebx,[ebp+8]
	lea  	eax, user_in
	push 	eax
	push 	LENGTHOF user_in
	push 	ebx
	lea  	eax, valid
	push 	eax
	call 	validate
	
	mov  	eax, valid
	cmp  	eax, TRUE
	jne  	get_loop
	
	lea  	eax, user_in
	push 	eax
	push 	LENGTHOF user_in
	call 	convertInt
	
	pop  	eax
	mov  	[ebp+8], eax

	ret 	
readVal 		ENDP

; validate(string in, int length, string error, int valid)
validate 		PROC 	USES 	esi ecx edi eax
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Procedure: 	  validate
; Description: 	  Takes a string, checks to see if all carachters are digits. Then checks is the digits
; 				  when converted are less than a defined limit.
; Receives: 	  address of String input, int length, error string, address of valid
; 				  (pushed in that order)
; Returns: 		  None, but modifes valid, for later checking
; Presoncditions: None
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LOCAL 			lim:DWORD
	mov  	lim, 429496729 	; 	not needed/used. but allows to use the LOCAL and help with organisation of
							; 	saving registers
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
;	push  	eax 	;save spcae for returning number
	push 	[ebp+20]
	push 	[ebp+16]
	call 	convertInt
	
	pop  	eax
	cmp  	eax, 429496729
	jg   	notDigit
	
	mov  	eax, [ebp+8] 	; 	change valude of valid
	mov  	ebx, TRUE
	mov  	[eax],ebx
	
val_quit:
;	pop  	ebp
	ret  	16
validate 		ENDP

; convertInt(string in, int length), returns the number on the stack
convertInt   	PROC 	USES esi ecx edx eax
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Procedure: 	 convertInt
; Description: 	 Converts a string of digits into an integer
; Receives: 	 string input, length of string
; Returns: 		 integer on the stack
; Preconditions: string in must have been checked to be valid.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FRAME
	
	mov  	esi, [ebp+28]
	mov  	ecx, [ebp+24]
	xor  	edx, edx
	xor  	eax, eax
	cld
convi_alg:
	lodsb
	cmp  	eax, 0
	je   	convi_done
	imul  	edx, edx, 10
	sub  	eax, "0"
	add  	edx, eax
	loop 	convi_alg

convi_done:
	mov  	[ebp+28], edx
	pop  	ebp
	ret  	4
convertInt  	ENDP

; arrayMath(int array[], int length), returns sum and average on the stack, pop sum first
arrayMath 		PROC 	USES eax esi ecx
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Procedure: 	 arrayMath
; Description: 	 Take an array of integers, sums them up, and finds the average of the numbers.
; Receives: 	 pointer to array, length of array
; Returns: 		 average, sum on stack, pop sum fist
; Preconditions: none
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LOCAL 			sum_loc:DWORD, avg_loc:DWORD, temp:DWORD
	
	mov  	eax, 0
	mov  	esi, [ebp+12]
	mov  	ecx, [ebp+8]
	mov  	temp, ecx
arrsum_loop:
	add  	eax, [esi]
	add  	esi, 4
	loop 	arrsum_loop
	
	mov  	sum_loc, eax
	
	fild 	sum_loc
	fidiv 	temp
	fistp	avg_loc
	
	mov  	eax, sum_loc
	mov  	[ebp+8], eax
	mov  	eax, avg_loc
	mov  	[ebp+12], eax
	
	ret 
arrayMath 		ENDP


; displayArray(int arr[], int length, string special)
displayArray 	PROC 	USES edx esi ecx ebx
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Procedure: 	 displayArray
; Description: 	 Takes an array, and displays each of the contained numbers.
; Receives: 	 pointer to array, length of array, string that contains a tab
; Returns: 		 none
; Preconditions: none
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FRAME
	mov  	esi, [ebp+32]
	mov  	ecx, [ebp+28]
	mov  	ebx, 0
	
display_loop:
	push 	[esi]
	call 	WriteVal
	mov  	edx, [ebp+24]
	call 	WriteString
	add 	esi, 4
	loop 	display_loop	
	pop  	ebp
	ret  	12	
displayArray 	ENDP

; writeVal(int number)
writeVal 		PROC 	USES eax edx
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Procedure: 	 writeVal
; Description: 	 Takes an integer, prints it out as a string.
; Receives: 	 integer
; Returns: 		 none
; Preconditions: none
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LOCAL 			str_out[MAX]:BYTE
	
	lea  	eax, str_out
	push 	eax
	push  	[ebp+8]		; 	integer to convert
	call 	convertChar
	
	lea  	eax, str_out
	displayString eax
	
	ret 	4
writeVal 		ENDP

; convertChar( string out, integer)
convertChar 	PROC 	USES eax ebx ecx edi
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Procedure: 	 convertChar
; Description: 	 takes an integer, and converts it to a string.
; Receives: 	 pointer to a string, integer to convert
; Returns: 		 none
; Preconditions: none
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LOCAL 			temp:DWORD
	
	mov  	eax, [ebp+8]
	mov  	ebx, base
	xor  	ecx, ecx
	
divide_again:
	xor  	edx, edx
	div  	ebx
	
	push  	edx
	inc  	ecx
	
	test 	eax, eax
	jnz  	divide_again
	
	mov  	edi, [ebp+12]
to_char:
	pop  	temp
	mov  	al, BYTE PTR temp
	add  	al, "0"
	stosb
	loop 	to_char
	mov  	al, 0
	stosb
	
	ret  	8
convertChar  	ENDP

END main
