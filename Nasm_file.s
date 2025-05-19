;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

%INCLUDE "stdlib.s"

section .text

_start:

	and rsp, -16

	mov rax, 0                                        ; rax = 0 
	mov [utyutyu], rax                                ; utyutyu = rax  ; number operator 2 
;---start-while-4--------------------------------------------------------------------------------
.start_while4:
;   test-4

	mov rax, [utyutyu]                                ; rax = utyutyu 
	mov rdx, 20                                       ; rdx = 20 
	cmp rax, rdx                                      ; if (rax > rdx)
	jg  .end_while4                                   ;  goto .end_while4
;   action-4

	mov rax, [utyutyu]                                ; rax = utyutyu 

	call _my_print                                    ; print (eax) ; number operator 6 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 8 

	mov rax, [utyutyu]                                ; rax = utyutyu 
	push rax                                          ; rax => stack
	mov rdx, 1                                        ; rdx = 1 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 11 
	mov [utyutyu], rax                                ; utyutyu = rax  ; number operator 11  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 12 
	jmp short .start_while4                           ;  goto .start_while4

.end_while4:

;---end-while-4---------------------------------------------------------------------------------- ; number operator 12  ; number operator 13  ; number operator 13  ; number operator 13 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

utyutyu: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
