TITLE Program 05     (Program05.asm)

; Author: 	Geoffrey Corey
; Course / Project ID   CS271 Program05             Date: 2-23-12
; Description: 	This program will get a number from the user between the range MAX and MIN, and generate MAX number of
; 				random integers, storing them in an array, print out the unsorted array, calculate the median of the 
; 				array, and then print out the sorted array.
;



;#####################################################################################################################
;################################################  Note to graders! ##################################################
;#####################################################################################################################                                     
;##                                                                                                                 ##
;##  This program will dynamically allocate a array of integers based upon the number the user                      ##
;##	enters. If it cannot allocate enough contiguous memory for the array, the program will exit.                   ##
;##	So please clear out some memory and re-run the application, not that you should really need                    ##
;##	to do that.                                                                                                    ##
;##	The dynamic array implementation will be adapted from the Kip Irvine example:                                  ##
;##	PDF with background explanation of the functions: http://kipirvine.com/asm/4th/articles/heap_allocation.pdf    ##
;##	ASM file: http://kipirvine.com/asm/4th/articles/heaptest.asm                                                   ##
;##                                                                                                                 ##
;##  Also, I hate the formatting and some text character difference between MS Visual Express and Notepad++!!!      ##
;##                                                                                                                 ##
;#####################################################################################################################
 	

INCLUDE Irvine32.inc

;	Macro definitions

;	macro for setting up stack frame
FRAME macro  				
		push 	ebp
		mov  	ebp, esp
ENDM

;	macro for division
MODULOUS macro item1, item2  
		mov  	eax, item1
		mov  	ebx, item2
		mov  	edx, 0
		div 	ebx
ENDM

; 	Literal Constants
NULL = 0
MAX  = 200
MIN  = 10
LO   = 100
HI   = 999
Programmer EQU <"Geoffrey Corey">

.data

; Strings
intro1 		BYTE 	10,13,"Sorting Random Integers 	Programmed by ",Programmer,10,13,\
					"This program generates random numbers in the range [",0
intro2 		BYTE 	" .. ",0
intro3 		BYTE 	"],",10,13,"displays the original list, sorts the list, and calculates the",\
					10,13,"median value. Finally, it displays the list in sorted descending order.",\
					10,13,10,13,10,13,0
request1  	BYTE 	"How many numbers should be generated? [",0
request2  	BYTE 	"]: ",0
error1 		BYTE 	10,13,"Invalid input. Try again.",10,13,0
error2    	BYTE 	10,13,"Cannot allocate enough contiguous memory.",10,13,"Please free some memory and rerun the",\
					"application",10,13,"The program will now exit.",10,13,0
arl1 		BYTE 	10,13,10,13,"The unsorted random numbers:",10,13,10,13,0
arl2 		BYTE 	10,13,10,13,"The sorted list:",10,13,10,13,0
median1		BYTE 	"The median is: ",0
spacing		BYTE 	" 	",0

; Integers
request		DWORD 	NULL 		     ; 	user selected number within the Min -> MAX range

; Array Allocation stuff, adapted from the Kip Irvine Example

; 	pointer to the memory block for the array
arrptr    	DWORD 	? 

; 	handle to the process heap
hHeap     	DWORD 	? 	               

; 	set memory bytes all to zero
dwFlags   	DWORD 	HEAP_ZERO_MEMORY 	

.code
main PROC	

; 	Seed random number generator
	call 	Randomize 	               
	
	push 	OFFSET intro1
	push  	OFFSET intro2
	push 	OFFSET intro3
	call 	introduction

	
	push 	OFFSET request1
	push 	OFFSET intro2
	push 	OFFSET request2
	push 	OFFSET error1
	push 	OFFSET request
	call 	getData
	

; 	Fixes allocation from BYTE to DWORD
	mov  	eax, request
	mov  	ebx, 4
	mul  	ebx
	mov  	edx, eax
	
;	Array allocation
	INVOKE 	GetProcessHeap
	mov  	hHeap, eax
	
;	Try to allocate memory for the array
	INVOKE HeapAlloc, hHeap, dwFlags, edx
	cmp  	eax, NULL
	je   	isNull
	mov  	arrptr, eax
	jmp  	continue
	
isNull:
	call 	Clrscr
	mov  	edx, OFFSET error2
	call 	WriteString
; 	Array cannot be allocated, exit program
	jmp  	quit 	

; 	Array has been allocated, continue with rest of function.	
continue:

	push 	OFFSET arl1
	push 	OFFSET spacing
	push 	arrptr
	push 	request
	call 	fillArray
	
	
	call  	displayList
	
	push 	arrptr
	push 	request
	call 	sortList
	
	push 	OFFSET median1
	push 	arrptr
	push 	request
	call 	displayMedian
	
	push 	OFFSET arl2
	push 	OFFSET spacing
	push 	arrptr
	push 	request
	call 	displayList
	
; 	Free the allocated array memory
	INVOKE 	HeapFree, hHeap, dwFlags, arrptr
	
	
	
	
quit:	
	exit	; exit to operating system
main ENDP

introduction 	PROC
;#########################################################################
;## Procedure: introduction                                             ##
;## Description: Prints out a friendly introduction explaining to the   ##
;##              user what the program will do.                         ##
;## Receives: intro1, intro2, intro3                                    ##
;## Returns: None                                                       ##
;## Preconditions: All the paramteters must be passed as an offset,     ##
;##                all parameters must be pushed in the order listed    ##
;##                in Receives.                                         ##
;## Registers: ebp, eax, edx                                            ##
;#########################################################################
	FRAME
	
; 	[ebp+16] = intro1
	mov  	edx, [ebp+16] 	
	call 	WriteString
	
	mov  	eax, LO 	
	call 	WriteDec
	
; 	[ebp+12] = intro2
	mov  	edx, [ebp+12] 	
	call 	WriteString
	
	mov  	eax, HI 	
	call 	WriteDec
	
; 	[ebp+8] = intro3
	mov  	edx, [ebp+8] 	
	call 	WriteString 
	
	pop  	ebp
	ret  	12
introduction 	ENDP

getData 		PROC
;############################################################################
;## Procedure: getData                                                     ##
;## Description: asks the user for an integer input within the range       ##
;## 			  MIN to MAX, validates the inpuut, and then stores         ##
;##			  that input.                                               ##
;## Receives: request1, intro2, request2, error1, request                  ##
;## Returns: none                                                          ##
;## Preconditions: All the paramteters must be passed as an offset,        ##
;## 			    all parameters must be pushed in the order              ##
;## 		         displayed by Receives.                                  ##
;## Registers: ebp, eax, edx                                               ##
;############################################################################
	FRAME
	
datasetup:

;	[ebp+24] = request1
	mov  	edx, [ebp+24] 	
	call 	WriteString

	mov  	eax, MIN
	call 	WriteDec
	
;	[ebp+20] = intro2
	mov  	edx, [ebp+20]
	call 	WriteString
	

	mov  	eax, MAX
	call 	WriteDec
	
;	[ebp+16] = request2
	mov  	edx, [ebp+16] 	
	call 	WriteString
	
dataread:
	call 	ReadInt
	
	cmp  	eax, MIN
	jl   	datantval
	
	cmp  	eax, MAX
	jg   	datantval

;	address of request
	mov  	ebx, [ebp+8]

;	store user input in request 	
	mov 	[ebx], eax 
	jmp  	datadone
datantval:

;	[ebp+12] = error1
	mov  	edx, [ebp+12] 	
	call 	WriteString 

	jmp  	datasetup

datadone:
	pop  	ebp
	ret  	20
getData 		ENDP

fillArray   	PROC
;#########################################################################
;## Procedure: fillArray                                                ##
;## Description: Fill the passed array with random numbers, repeated    ##
;## 			   user requested number of times.                       ##
;## Receives: arrptr, request                                           ##
;## Returns: none                                                       ##
;## Preconditions: arrptr must be a pointer to the array, and           ##
;## 			    the parameters must be pushed on the stack in the    ##
;## 			    order shown in Receives.                             ##
;## Registers: ebp, esi, eax, edx, ecx                                  ##
;#########################################################################
	FRAME
	mov  	eax, (HI-LO)+1

; 	[ebp+8] = request
	mov  	ecx, [ebp+8] 	
	mov  	edx, 0
	
; 	[ebp+12] = arrptr
	mov  	esi, [ebp+12]
 	
fillgenerate:

	call 	RandomRange
	add  	eax, LO
	mov  	[esi], eax
	add  	esi, 4
	loop 	fillgenerate
	
	pop  	ebp
	ret
fillArray	 	ENDP

sortList 		PROC
LOCAL       	request_loc:DWORD
;#########################################################################
;## Procedure: sortList                                                 ##
;## Description: Sorts the passed array in descending value             ##
;## Receives: arrptr, request                                           ##
;## Returns: none                                                       ##
;## Preconditions: arrptr must be a pointer to the array, must be       ##
;## 			    onto the stack in the order listed in Received       ##
;## Registers: ebp, esi, eax, edx, ecx                                  ##
;#########################################################################


; 	Setting up variables and registers.
	mov  	eax, [ebp+8]
	
; 	request_loc = request = # of array elements
	mov  	request_loc, eax 

; 	fix array 0 offset	
	dec  	request_loc

; 	esi = array	
	mov  	esi, [ebp+12] 	
	
	
; 	Sorting algorithm == bubble sort.
	mov  	ecx, request_loc
	
outterLoop:

; 	save outterLoop count
	push 	ecx  
	
; 	reset innerLoop count
	mov  	ecx, request_loc
	
; 	reset esi to beggining of array
	mov  	esi, [ebp+12] 
	
innerLoop:

	mov  	eax, [esi]
	
; 	if array[i] > array[i+1]
	cmp  	[esi+4], eax 	
	jl   	lessThan
	
; 	swap array[i] with array[i+1]
	push 	[esi+4]
	push 	[esi]
	call 	exchange
	pop  	[esi]
	pop  	[esi+4]

lessThan:
; 	i++
	add  	esi, 4
	loop 	innerLoop
	
; 	restore outterLoop count
	pop  	ecx
	loop 	outterLoop	
	
sortFinish:
	ret  	8
sortList 		ENDP

exchange 		PROC
;#########################################################################
;## Procedure: exchange                                                 ##
;## Description: Exchanges array[i] with array[j]                       ##
;## Receives: array[i], array[j]                                        ##
;## Returns: array[j], array[i]                                         ##
;## Preconditions: all parameters must be pushed in the order listed    ##
;##                in Receives.                                         ##
;## Registers: ebp, eax, ebx                                            ##
;#########################################################################

	FRAME
	
;	[ebp+12] = array[i]
	mov  	eax, [ebp+12]
	
;	[ebp+8] = array[j]
	mov  	ebx, [ebp+8]
	
;	swap array[i] with array[j]
	mov  	[ebp+12], ebx
	mov  	[ebp+8], eax
	
	pop  	ebp
	ret
exchange 		ENDP

displayMedian 	PROC
LOCAL   		sizear:DWORD, median:DWORD, medlo:DWORD, medhi:DWORD, divisor:DWORD
;#########################################################################
;##	Procedure: displayMedian                                           ##
;##	Description: Calculates the median value of the numbers in the     ##
;## 			   passed array                                          ##
;## Receives: median1, arrptr, request                                  ##
;## Returns: none                                                       ##
;## Preconditions: arrptr must be apointer to the array, parameters     ##
;##                must be pushed in the order listed in Receives,      ## 
;##                median 1 must be passed as a offset                  ##
;## Registers: ebp, eax, esi, ebx,	edx                                  ##
;#########################################################################
	call 	Crlf
	call 	Crlf
	
;	[ebp+8] = request
	mov  	eax, [ebp+8]
	
;	[ebp+12] = arrptr
	mov  	esi, [ebp+12]
	
	mov  	sizear, eax
	mov  	divisor, 2
	
;	calculate middle of array
MODULOUS  	sizear, 2
	mov  	median, eax

	mov  	eax, median
	mov  	ebx, 4
	mul  	ebx
	mov  	ecx, eax

;	median value of array, regardless of even or odd
	mov  	eax, [esi+ecx]
	mov  	medhi, eax
	
;	median value + 1 index, for even number array
	mov  	eax, [esi+ecx-4]
	mov  	medlo, eax

;	Check if array length is even or odd.
MODULOUS  	sizear, 2
	cmp  	edx, 0
	jg   	medianPrint

;	Calculate difference between two middle values in even length array	
	fild 	medhi
	fiadd 	medlo
	fidiv 	divisor
	fistp 	medhi
	
medianPrint:

;	[ebp+16] = median1 string
	mov  	edx, [ebp+16]
	call 	WriteString
	
	mov  	eax, medhi
	call 	WriteDec
	call 	Crlf

medianDone:
	ret  	12
displayMedian 	ENDP

displayList 	PROC
;#########################################################################
;## Procedure: displayList                                              ##
;## Description: displays a banner indiccating they typre of list       ##
;##              as well as the contents of the passed array in	       ##
;##              an aligned column format, ten elements per row.        ##
;## 			  passed array                                           ##
;## Receives: 										            ##
;## Returns: array[j], array[i]								  ##
;## Preconditions: none										  ##
;## Registers: ebp, eax, esi, ecx, ebx                                  ##
;#########################################################################

	FRAME
	
;	[ebp+20] = arl1 or arl2, depending on call from main
	mov  	edx, [ebp+20] 	
	call 	WriteString

;	[ebp+8] = request	
	mov  	ecx, [ebp+8] 

;	[ebp+16] = spacing, for lining up columns on print	
	mov  	edx, [ebp+16] 

;	[ebp+12] = arrptr	
	mov  	esi, [ebp+12] 
	
	mov  	ebx, 0

displayLoop:

;	[esi] = value of array at current index
	mov  	eax, [esi]
	call 	WriteDec
	
;	print spacing (tab)
	call 	WriteString

;	mov to next index of array	
	add  	esi, 4
	
	cmp  	ebx, 10
	jne  	displaynot10

;	reset counter to 0 for next row of numbers
	mov  	ebx, 0
	inc  	ebx
	call 	Crlf
	
displaynot10:

	loop 	displayLoop

;	Visual output structure, add in some whitespace in output.
	call 	Crlf
	call 	Crlf
	
	pop  	ebp
	ret  	16
displayList 	ENDP

END main
