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

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, 0                                        ; rax = 0 
	mov [utyutyu], rax                                ; utyutyu = rax  ; number operator 5 
;---start-while-7--------------------------------------------------------------------------------
.start_while7:
;   test-7

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = utyutyu 
	mov rdx, 20                                       ; rdx = 20 
	cmp rax, rdx                                      ; if (rax > rdx)
	jg  .end_while7                                   ;  goto .end_while7
;   action-7

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = utyutyu 

	call _my_print                                    ; print (eax) ; number operator 9 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 11 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = utyutyu 
	push rax                                          ; rax => stack
	mov rdx, 1                                        ; rdx = 1 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 14 
	mov [utyutyu], rax                                ; utyutyu = rax  ; number operator 14  ; number operator 15  ; number operator 15  ; number operator 15  ; number operator 15 
	jmp short .start_while7                           ;  goto .start_while7

.end_while7:

;---end-while-7---------------------------------------------------------------------------------- ; number operator 15  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 17  ; number operator 17 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
