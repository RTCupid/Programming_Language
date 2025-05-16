;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

section .text

%INCLUDE "stdlib.s"

_start:

	and rsp, -16

	mov rax, 8

	call _my_print
;number operator 2 ;number operator 3 ;number operator 3 
	call _my_hlt

section .note.GNU-stack
