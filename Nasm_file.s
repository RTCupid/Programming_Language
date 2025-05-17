;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

%INCLUDE "stdlib.s"

section .text

_start:

	and rsp, -16

;--------------------------------------------------------------------------------------------------
;	my_main:
;--------------------------------------------------------------------------------------------------

my_main:                                              ; it is definition of my_main  ; number operator 3 

	call _my_input                                    ; input(number); rax = input 
	mov [number], rax                                 ; [number] = rax  ; number operator 5 

	mov rax, [number]                                 ; rax = number 

	movq xmm0, rax                                    ; xmm0 = rax

	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)

	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 8 
	mov [answer], rax                                 ; answer = rax  ; number operator 8 

	mov rax, [answer]                                 ; rax = answer 

	call _my_print                                    ; print (eax) ; number operator 10  ; number operator 11  ; number operator 11  ; number operator 11  ; number operator 11  ; number operator 11  ; number operator 12  ; number operator 12 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

number: dq 0
answer: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
