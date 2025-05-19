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

	call _my_input                                    ; input(argument); rax = input 
	mov [argument], rax                               ; [argument] = rax  ; number operator 5 

	mov rax, [argument]                               ; rax = argument 

	push rax                                          ; rax => stack, make stack frame;

	call Factorial                                    ; Factorial (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 8 
	mov [answer], rax                                 ; answer = rax  ; number operator 8 

	mov rax, [answer]                                 ; rax = answer 

	call _my_print                                    ; print (eax) ; number operator 10 

	call _my_hlt                                      ; exit (0) ; number operator 12  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 13 

;--------------------------------------------------------------------------------------------------
;	Factorial:
;--------------------------------------------------------------------------------------------------

Factorial:                                            ; it is definition of Factorial  ; number operator 16 
;---start-if-18-----------------------------------------------------------------------------------
;   test-18

	mov rax, [fact]                                   ; rax = fact 
	mov rdx, 3                                        ; rdx = 3 
	cmp rax, rdx                                      ; if (rax >= rdx)
	jge  .end_if18                                    ;  goto .end_if18
;   action-18

	mov rax, 2                                        ; rax = 2 

	ret                                               ; return; ; number operator 20  ; number operator 21  ; number operator 21 

.end_if18:

;---end-if-18------------------------------------------------------------------------------------- ; number operator 21 

	mov rax, [fact]                                   ; rax = fact 
	push rax                                          ; rax => stack

	mov rax, [fact]                                   ; rax = fact 
	push rax                                          ; rax => stack
	mov rdx, 1                                        ; rdx = 1 
	pop rax                                           ; rax <= stack
	sub rax, rdx                                      ; rax -= rdx ; number operator 26 

	push rax                                          ; rax => stack, make stack frame;

	call Factorial                                    ; Factorial (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 26 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi ; number operator 26 

	ret                                               ; return; ; number operator 26  ; number operator 27  ; number operator 27  ; number operator 27  ; number operator 27  ; number operator 28  ; number operator 28  ; number operator 28 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

argument: dq 0
answer: dq 0
fact: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
