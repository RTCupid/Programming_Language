;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

%INCLUDE "stdlib.s"

section .text

_start:

	and rsp, -16

;----------------------------------------------------------------------------------------
;	my_main:
;----------------------------------------------------------------------------------------
my_main:;number operator 3 

	call Factorial;number operator 5 
	mov rax, 7

	call _my_print;number operator 7 

	call _my_hlt;number operator 9 ;number operator 10 ;number operator 10 ;number operator 10 ;number operator 10 ;number operator 10 

;----------------------------------------------------------------------------------------
;	Factorial:
;----------------------------------------------------------------------------------------
Factorial:;number operator 13 
	mov rax, 8

	call _my_print;number operator 15 
	mov rax, 0

	ret;number operator 17 ;number operator 18 ;number operator 18 ;number operator 18 ;number operator 18 ;number operator 19 ;number operator 19 ;number operator 19 
	call _my_hlt

section .note.GNU-stack
