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

	call _my_input                                    ; input(a); rax = input 
	mov [a], rax                                      ; [a] = rax  ; number operator 5 

	mov rax, [a]                                      ; rax = a 

	call _my_print                                    ; print (eax) ; number operator 7  ; number operator 8  ; number operator 8  ; number operator 8  ; number operator 8  ; number operator 9  ; number operator 9 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

a: dd 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
