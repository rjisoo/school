TITLE Program02     (Program02.asm)

; Author: Geoffrey Corey
; Course / Project ID     CS 271 Program02        Date: 1-25-12
; Description: Get the user's name, and get the number of fibonacci numbers the user wants calculated
;			   ranging between 1 and 46 inclusive, and validate the input to be within the range, and
;			   output the results and the user's name in a readable format.

;Programming note: I used Notepad++ to write this, and didn't realise the spacing was off
;				   in Visual Studio on the tab/space in the source until after i submitted.

INCLUDE Irvine32.inc

NAME_LENGTH = 24

; (insert symbol definitions here)

.data

; strings
header1 	BYTE 	"Fibonacci Numers",0
header2 	BYTE 	"Programmed by Geoffrey Corey",0
question1 	BYTE	"What's your name? ",0
question2 	BYTE 	"Hello, ",0 
direction1 	BYTE 	"Enter the number of Fibonacci terms to be displayed.",0
direction2 	BYTE 	"Give a number as an integer in the range [1 ... 46].",0
end_sent	BYTE	"!",0 
num_fib 	BYTE 	"How many Fibonacci terms do you want? ",0
num_err 	BYTE 	"Error, number out of range. Enter anumber in the range [1 ... 46]",0
certified 	BYTE 	"Results certified by Geoffrey Corey",0
goodbye 	BYTE 	"Goodbye, ",0
user_name 	BYTE 	NAME_LENGTH DUP(?)

;integers
user_num 	DWORD 	?
fib1 		DWORD	0
fib2 		DWORD 	1


; (insert variables here)

.code
main PROC

introduction:
; 	Writes the programmer's name, and the intent of the program.
	call 	Crlf
	mov 	edx, OFFSET header1
	call 	WriteString
	call	Crlf
	mov 	edx, OFFSET header2
	call 	WriteString
	call 	Crlf
	call 	Crlf
	
userInstruction:
;	Asks the user their name, reads the input, and displays the name back to them.
;	It then tells the user about number input, and the range of the number to select.
	mov 	edx, OFFSET question1
	call	WriteString
	mov 	edx, OFFSET user_name
	mov 	ecx, NAME_LENGTH
	call 	ReadString
	call 	Crlf
	mov 	edx, OFFSET question2
	call 	WriteString
	mov		edx, OFFSET user_name
	call 	WriteString
	mov 	edx, OFFSET end_sent
	call 	WriteString
	call 	Crlf
	mov 	edx, OFFSET direction1
	call 	WriteString
	call 	Crlf
	mov 	edx, OFFSET direction2
	call 	WriteString
	call 	Crlf
	call 	Crlf
	
getUserData:
;	Gets the number the user inputs, checks if it's a number, and checks if the number is within
;	the acceptable range, reporting and error and reasking for a number if it's not acceptable.
	mov 	edx, OFFSET num_fib
	call 	WriteString
	call 	ReadInt
	mov 	user_num, eax
	cmp 	user_num, 46
	jle 	lessequ46
	jmp 	errorNum
	
lessequ46:
;	Part of the data validation block, if the input <=46, goes to greatereq1 block
	cmp 	user_num, 1
	jge 	greaterequ1
	jmp 	errorNum
	

greaterequ1:
;	If it gets here, the number is <=46 or >=1, and will go into doing the Fibonacci sequence.
	jmp 	displayFibs

errorNum:
;	Produces and error message about range, and starts the reprompt.
	mov 	edx, OFFSET num_err
	call 	WriteString
	call 	Crlf
	jmp 	getUserData

displayFibs:
;	First step in the fib. seq. calcuations, and takes the first term into accoutn, priting the first
;	1 of the seq, and changes the counter to see fit and checks if the counter will cause the next
;	part of the loop to into infinate loop.
	mov 	eax, 1
	call 	WriteDec
	call 	Crlf
	dec 	user_num
	cmp 	user_num, 0
	je		farewell
	mov 	ecx, user_num
	
	
fibAlgo:
;	Calculates the rest of the fib. seq. until the counter reaches zero, withthe first 1 taken into account.
	mov 	eax, fib1
	mov 	ebx, fib2
	mov 	fib1, ebx
	add 	eax, ebx
	mov 	fib2, eax
	call 	WriteDec
	call	Crlf
	loop 	fibAlgo

	
farewell:
; 	Displays results certification, the user name, and goodbye.
	call 	Crlf
	mov 	edx, OFFSET certified
	call 	WriteString
	call 	Crlf
	mov 	edx, OFFSET goodbye
	call 	WriteString
	mov 	edx, OFFSET user_name
	call 	WriteString
	mov 	edx, OFFSET end_sent
	call	WriteString
	call 	Crlf
	call 	Crlf
	
	

; (insert executable instructions here)

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
