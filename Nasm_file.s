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
	mov rax, 10
	pop [1]; x
;number operator 5 
	mov rax, 20
	pop [2]; y
;number operator 7 
	mov rax, 3
	pop [3]; z
;number operator 9 
	mov rax, [1]; x

	mov rdx, [2]; y

	add rax, rdx;number operator 12 
	pop [4]; sum
;number operator 12 
	mov rax, [4]; sum


	call _my_print;number operator 14 
	mov rax, [1]; x

	mov rdx, [3]; z

	mul rax, rdx;number operator 17 
	pop [5]; mult
;number operator 17 
	mov rax, [5]; mult


	call _my_print;number operator 19 
	mov rax, [4]; sum

	mov rdx, [3]; z

	div rax, rdx;number operator 22 
	pop [6]; divi
;number operator 22 
	mov rax, [6]; divi


	call _my_print;number operator 24 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 26 ;number operator 26 
	call _my_hlt

section .note.GNU-stack
