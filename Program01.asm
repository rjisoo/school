TITLE Program01     (Program01.asm)

; Author: Geoffrey Corey
; Course / Project ID   CS271 Program01              Date: 1-23-12
; Description: Get 2 integers from user input, add and subtract the two values and store the answers,
;			   multiply and divide the two value and store the answers, and finally display the sum, quotient, 
;			   product and difference.

INCLUDE Irvine32.inc

; (insert symbol definitions here)

.data

header BYTE "Elemntary Arithmetic     by Geoffrey Corey",0
do_this BYTE "Enter 2 integers, and I'll show you the sum, difference,",0
do_this2 BYTE "product, quotient, and remainder.",0

get1 BYTE "Please input the first integer, not equal to zero.",0
get2 BYTE "Please input a second integer, not equal to zero.",0

plus BYTE " + ",0
minus BYTE " - ",0
multiply BYTE " x ",0
divide BYTE " / ",0
equal BYTE " = ",0
remainder BYTE " remainder ",0

num1 BYTE "Integer1= ",0
num2 BYTE "Integer2 = ",0

lastq1 BYTE "Impressed?",0
lastq2 BYTE "Bye!",0

first_num SDWORD ?
sec_num SDWORD ?

quot SDWORD ?
prod SDWORD ?
diff SDWORD ?
sum SDWORD ?
remain SDWORD ?


; (insert variables here)

.code
main PROC

Instructions:
;	Writes the intro and instructions to the screen.
	call Crlf
	mov  edx,OFFSET header
	call WriteString
	call Crlf
	call Crlf
	call Crlf
	
	mov  edx,OFFSET do_this
	call WriteString
	call Crlf
	mov  edx, OFFSET do_this2
	call WriteString
	call Crlf
	call Crlf
	
Input1:

;	Gets the user input for the rest of the operations.
	call Crlf
	mov  edx,OFFSET get1
	call WriteString
	call Crlf
	mov edx,OFFSET num1
	call WriteString
	call ReadInt
	cmp  eax,0
	JE Input1
	call Crlf
	mov first_num,eax

Input2:

;	Same as Input1	
	mov  edx,OFFSET get2
	call WriteString
	call Crlf
	mov edx,OFFSET num2
	call WriteString
	call ReadInt
	cmp  eax,0
	JE Input2
	call Crlf
	mov sec_num,eax
	call Crlf
	call Crlf
	
Arithmetic:
;	Does the arithmetic part of the program.

	mov  eax,first_num
	mov  ebx,sec_num
	imul ebx
	mov  prod,eax ;after multiplying first_num and sec_num, puts the answer in the product variable.
	
	mov  eax,first_num
	mov  edx,0
	mov  ebx,sec_num
	cdq
	idiv ebx
	mov  quot,eax   ;and puts the quotient in the quot variable.
	mov  remain,edx ;after dividing first_num by sec_num, puts the remainder in the remain variable,
	
	mov  eax,first_num
	add  eax,sec_num
	mov  sum,eax        ;adds sec_num to first_num and stores in sum variable.
	
	mov  eax,first_num
	sub  eax,sec_num
	mov  diff,eax      ;subtracts sec_numb from first_num and stores in diff variable.
	
Output:

;	Output for addition
	mov  eax,first_num
	call WriteInt
	mov  edx,OFFSET plus
	call WriteString
	mov  eax,sec_num
	call WriteInt
	mov  edx,OFFSET equal
	call WriteString
	mov  eax,sum
	call WriteInt
	call Crlf
	
;	Output for subtraction
	mov  eax,first_num
	call WriteInt
	mov  edx,OFFSET minus
	call WriteString
	mov  eax,sec_num
	call WriteInt
	mov  edx,OFFSET equal
	call WriteString
	mov  eax,diff
	call WriteInt
	call Crlf
	
;	Output for multiplication
	mov  eax,first_num
	call WriteInt
	mov  edx,OFFSET multiply
	call WriteString
	mov  eax,sec_num
	call WriteInt
	mov  edx,OFFSET equal
	call WriteString
	mov  eax,prod
	call WriteInt
	call Crlf
	
;	Output for division
	mov  eax,first_num
	call WriteInt
	mov  edx,OFFSET divide
	call WriteString
	mov  eax,sec_num
	call WriteInt
	mov  edx,OFFSET equal
	call WriteString
	mov  eax,quot
	call WriteInt
	mov  edx,OFFSET remainder
	call WriteString
	mov  eax,remain
	call WriteInt
	call Crlf
	call Crlf
	call Crlf
	
Procede:

;	Prints out a last sentence saying bye.
	mov  edx,OFFSET lastq1
	call WriteString
	call Crlf
	mov  edx,OFFSET lastq2
	call WriteString
	call Crlf
	call Crlf
	
	
; (insert executable instructions here)

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
