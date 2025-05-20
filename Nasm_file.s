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

	push rbp                                          ; rbp => stack, save old value of rbp

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 16] = function's argument

	mov rax, 3125                                     ; rax = 3125 
	mov [x], rax                                      ; x = rax  ; number operator 5 

	mov rax, qword [x]                                ; rax = x 

	call _my_print                                    ; print (eax) ; number operator 7  ; number operator 8  ; number operator 8  ; number operator 8  ; number operator 8  ; number operator 9  ; number operator 9 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

x: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
