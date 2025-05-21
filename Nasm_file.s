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

	call _my_input                                    ; input(argument); rax = input 
	mov [argument], rax                               ; [argument] = rax  ; number operator 5 

	mov rax, qword [argument]                         ; rax = argument 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Factorial                                    ; Factorial (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 8 
	mov [answer], rax                                 ; answer = rax  ; number operator 8 

	mov rax, qword [answer]                           ; rax = answer 

	call _my_print                                    ; print (rax) ; number operator 10 

	call _my_hlt                                      ; exit (0) ; number operator 12  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 13  ; number operator 13 

;--------------------------------------------------------------------------------------------------
;	Factorial:
;	Entry: after saving rbp:
;	Entry: number = [rsp + 16]
;	Entry: [rsp + 8] = adress to return
;	Entry: [rsp] = rbp
;--------------------------------------------------------------------------------------------------

Factorial:                                            ; it is definition of Factorial  ; number operator 16 

	push rbp                                          ; rbp => stack, save old value of rbp

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 16] = function's argument
;---start-if-18-----------------------------------------------------------------------------------
;   test-18

	mov rax, qword [rbp + 16]                         ; rax = number 
	mov rdx, 2                                        ; rdx = 2 
	cmp rax, rdx                                      ; if (rax >= rdx)
	jge  .end_if18                                    ;  goto .end_if18
;   action-18

	mov rax, 1                                        ; rax = 1 

	mov rsp, rbp                                      ; rsp = rbp; back old value rsp;

	pop rbp                                           ; rbp <= stack, back old value of rbp

	ret                                               ; return; ; number operator 20  ; number operator 21  ; number operator 21 

.end_if18:

;---end-if-18------------------------------------------------------------------------------------- ; number operator 21 
;---start-if-23-----------------------------------------------------------------------------------
;   test-23

	mov rax, qword [rbp + 16]                         ; rax = number 
	mov rdx, 3                                        ; rdx = 3 
	cmp rax, rdx                                      ; if (rax >= rdx)
	jge  .end_if23                                    ;  goto .end_if23
;   action-23

	mov rax, 2                                        ; rax = 2 

	mov rsp, rbp                                      ; rsp = rbp; back old value rsp;

	pop rbp                                           ; rbp <= stack, back old value of rbp

	ret                                               ; return; ; number operator 25  ; number operator 26  ; number operator 26 

.end_if23:

;---end-if-23------------------------------------------------------------------------------------- ; number operator 26 

	mov rax, qword [rbp + 16]                         ; rax = number 
	push rax                                          ; rax => stack

	mov rax, qword [rbp + 16]                         ; rax = number 
	push rax                                          ; rax => stack
	mov rdx, 1                                        ; rdx = 1 
	pop rax                                           ; rax <= stack
	sub rax, rdx                                      ; rax -= rdx ; number operator 31 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Factorial                                    ; Factorial (rax);

	add rsp, 8                                        ; clean stack frame;

	mov rdx, rax                                      ; rdx = rax ; number operator 31 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi ; number operator 31 

	mov rsp, rbp                                      ; rsp = rbp; back old value rsp;

	pop rbp                                           ; rbp <= stack, back old value of rbp

	ret                                               ; return; ; number operator 31  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 33  ; number operator 33  ; number operator 33 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

argument: dq 0
answer: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
