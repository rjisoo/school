TITLE Program Template     (template.asm)

; Author: 	Geoffrey Corey
; Course / Project ID     CS271 Program04            Date: 	2-15-12
; Description: 	Ask the user for a input ranging between 1 and 200, and shows the user 
;				that many calculated prime numbers, starting from 2.

; 		  Note to graders, I am using NotePad++ to type this, so some of the formatting may
;		  not carry over correctly into MS Visual Studio


INCLUDE Irvine32.inc


Upper_lim 	= 	200
Base_loop 	=	2 	;change this to 1 if you would like to include 1 as being a prime number.
Programmer 	EQU 	<"Geoffrey Corey.",0>

.data

;strings
name1 		BYTE 	"Prime Numbers. 	Programmed by ",0
name2 		BYTE 	Programmer
direction1 	BYTE 	"Enter the number of prime numbers you would like to see.",0
direction2 	BYTE 	"I'll accept orders for up to ",0
direction3 	BYTE 	" primes.",0
direction4	BYTE 	"Enter the number of primes to display [1 .. ",0
direction5 	BYTE 	"]: ",0
error1 		BYTE 	"Out of range. Try again.",0
spacing		BYTE 	" 	",0
certified1 	BYTE 	"Results certified by ",0	
certified2 	BYTE 	" 	Goodbye.",0

;integers
usernum   	DWORD 	?
numcheck  	DWORD	Base_loop
arryptr   	DWORD 	?
tmpval 		DWORD 	?
root 		DWORD 	?
remainder 	DWORD 	?
count 		DWORD 	0

;array
arrayPrime 	DWORD	Upper_lim DUP(0)
 

.code
main 			PROC

;	Prints the programmed by string, and begins to call the procedures
		call 	Crlf
		call 	Crlf
		mov  	edx, OFFSET name1
		call 	WriteString
		mov  	edx, OFFSET name2
		call 	WriteString
		call 	Crlf
		
; 	initializes the pointer to the array of primes for a later use.
		mov  	eax, OFFSET arrayPrime
		mov  	arryptr, eax
		
; 	begins the execution of program procedures.
		call 	introduction
		call 	getUserData
		call 	showPrimes
		call 	farewell

		exit	; exit to operating system
main 			ENDP


introduction 	PROC
; Prints out an introduction statemtn about what the program will do.
; Receives: 			direction1, direction2, direction3 are global variables
; Returns: 				none.
; Preconditions: 		none.
; Registers Changed: 	edx

;	 writes friendly first direction
		call 	Crlf
		mov  	edx, OFFSET direction1
		call 	WriteString
		call 	Crlf
;	 writes upper limit of acceptance using the Upper_limit constant
		mov  	edx, OFFSET direction2
		call 	WriteString
		mov  	eax, Upper_lim
		call 	WriteDec
		mov  	edx, OFFSET direction3
		call 	WriteString
		call 	Crlf
		ret
introduction 	ENDP

getUserData 	PROC
; Directs the user on entering valid input, and then checks the data for validity.
; Receives: 			direction4, direction5 are global variables, Upper_lim is a literal.
; Returns: 				usernum is a globabl variable.
; Preconditions: 		none.
; Registers Changed: 	edx, eax.

;	prompts the user for input with the upper limit
		call 	Crlf
		mov  	edx, OFFSET direction4
		call 	WriteString
		mov  	eax, Upper_lim
		call 	WriteDec
		mov  	edx, OFFSET direction5
		call 	WriteString
		
;	gets user input
		call 	ReadInt
		mov  	usernum, eax
		call 	validate
		ret
getUserData 	ENDP

	validate 		PROC 
; Validates the user input being within the assignment specified range.
; Receives: 			usernum, error1 are global variables. Upper_lim is a literal
; Returns: 				none
; Preconditions: 		none.
; Registers Changed: 	edx.

;	internal function, used in getUserData
;		checks user input to see if in range
			cmp  	usernum, Upper_lim
			jg 		wrong 	
		
		lessEq:
;		input is <= 200
			cmp  	usernum, 1
			jl 		wrong
			jmp  	success ; 1 <= usernum <= 200 if execution reaches here.
		
		wrong:
;		Input out of range, calls getUserData to try again.
			mov  	edx, OFFSET error1
			call 	WriteString
			call 	Crlf
			call 	getUserData
		
		success:
			ret
	validate 		ENDP

showPrimes 		PROC
; Shell function, used o calculate prime numbers, and show them 10 per line.
; Receives: 			none.
; Returns: 				none.
; Preconditions: 		none.
; Registers Changed: 	none.
		call 	isPrime
		call 	printArray
		ret
showPrimes 		ENDP

	isPrime 		PROC 
; Loops the function that calculate prime numbers n times.
; Receives: 			usernum.
; Returns: 				none.
; Preconditions: 		none.
; Registers Changed: 	ecx.

;	internal function, used in the showPrimes function
			mov  	ecx, usernum
		primeloop:
			call 	primesFunction
			loop 	primeloop
			ret
	isPrime 		ENDP
	
	primesFunction 	PROC
; Calculates the next prime number and adds it to the array of prime numbers..
; Receives: 			numcheck is a globabl variable.
; Returns: 				root, tmpval are global variables.
; Preconditions: 		none.
; Registers Changed: 	ecx, st, eax, ebx, edx.

; 	internal function, used in isPrime function
		comproot:
; 	Computes square root of the number to check using floating point operations.
			fild 	numcheck 	;copies numcheck to fpu data register
			fsqrt
			fistp 	root		;copies from fpu data register to variable root.
		rootcheck:
;	checks if root is 1. if it is, then we have a prime, otherwise, divide numcheck by root.
			mov  	eax, root
			cmp  	eax, 1
			je   	gotprime
			mov  	eax, numcheck
			mov  	ebx, root
			mov  	edx, 0
			div  	ebx
			cmp  	edx, 0
			jne  	remainnot0
		remain0:
;	there is no remainder, so numcheck isn't prime. start checking next number.
			inc  	numcheck
			jmp  	comproot		
		remainnot0:
;	there is a remainder, so decrese root, and check again.
			dec  	root
			jmp  	rootcheck			
		gotprime:
; 	we have a prime number, add it to the array, and return to the isPrime function
			mov  	eax, numcheck
			mov  	tmpval, eax
			call 	addtoArray
			jmp  	back
		back:
; 	increments numcheck for next prime checking iteration.
			inc  	numcheck
			ret			
	primesFunction	ENDP

	addToArray 		PROC 
; Adds tmpval to the arrayPrimes array.
; Receives: 			arryptr, tmpval are globabl variables.
; Returns: 				arryptr is a globabl variable.
; Preconditions: 		none.
; Registers Changed: 	esi, eax.

;	internal function, used in the _isPrime function.
			mov  	esi, arryptr 	;loads the pointer to the next empty spot in the array.
			mov  	eax, tmpval	
			mov  	[esi], eax	 	;puts the temp value in the array
			add  	esi, 4
			mov  	arryptr, esi 	;update arryptr to next open location.
			ret
	addToArray 		ENDP
	
	printArray		PROC
; APrints outthe contents of the array n times, where n is the number the user selected.
; Receives: 			arraPrime, usernum, spacing, count are globabl variables.
; Returns: 				count is a globabl variable.
; Preconditions: 		none.
; Registers Changed: 	esi, ecx, ebx, edx.

			mov  	esi, OFFSET arrayPrime 	;loads the array offset.
			mov  	ecx, usernum
			call 	Crlf
		gothrough:
			;call 	Crlf
			mov  	eax, [esi] 				;copies the content of current location.
			call 	WriteDec				;displays the contents of the array at the current point.
			mov  	edx, OFFSET spacing
			call 	WriteString
			add  	esi, 4					;increnments to the next position in the array.
			mov  	ebx, count
			cmp  	edx, 10 				;checks if count is 10. if it is, it calls a Crlf and sets count
			jne  	ifnot10 				;to 0.
			call 	Crlf
			mov  	ebx, 0
			mov  	count, ebx
		ifnot10:
			loop 	gothrough
			ret
	printArray 		ENDP

farewell 		PROC
; Prints out the farewell message and certification.
; Receives: 			certified1, certified2, name2 are globabl variables.
; Returns: 				none.
; Preconditions: 		none.
; Registers Changed: 	edx.
; 	Provides a farewell message to the user, using the string literal for programmer's name.
		call 	Crlf
		call 	Crlf
		mov  	edx, OFFSET certified1
		call 	WriteString
		mov  	edx, OFFSET name2
		call 	WriteString
		mov  	edx, OFFSET certified2
		call 	WriteString
		call 	Crlf
		call 	Crlf
		ret
farewell 		ENDP

END main
