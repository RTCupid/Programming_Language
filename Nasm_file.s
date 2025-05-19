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

	call _my_input                                    ; input(utyutyu); rax = input 
	mov [utyutyu], rax                                ; [utyutyu] = rax  ; number operator 5 
;---start-if-7-----------------------------------------------------------------------------------
;   test-7

	mov rax, [utyutyu]                                ; rax = utyutyu 
	mov rdx, 20                                       ; rdx = 20 
	cmp rax, rdx                                      ; if (rax >= rdx)
	jge  .end_if7                                     ;  goto .end_if7
;   action-7

	mov rax, [utyutyu]                                ; rax = utyutyu 

	call _my_print                                    ; print (eax) ; number operator 9 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 11  ; number operator 12  ; number operator 12  ; number operator 12 

.end_if7:

;---end-if-7------------------------------------------------------------------------------------- ; number operator 12  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 14  ; number operator 14 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

utyutyu: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
