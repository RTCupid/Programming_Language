;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

%INCLUDE "stdlib.s"

section .text

_start:

	and rsp, -16

	mov rax, 7                                        ; rax = 7 
	mov [a], rax                                      ; a = rax  ; number operator 2 

	mov rax, 12                                       ; rax = 12 
	mov [b], rax                                      ; b = rax  ; number operator 4 

	mov rax, 4                                        ; rax = 4 
	mov [c], rax                                      ; c = rax  ; number operator 6 

	mov rax, 100000000                                ; rax = 100000000 
	mov [ntimes], rax                                 ; ntimes = rax  ; number operator 8 
;---start-while-10--------------------------------------------------------------------------------
.start_while10:
;   test-10

	mov rax, qword [ntimes]                           ; rax = ntimes 
	mov rdx, 1                                        ; rdx = 1 
	cmp rax, rdx                                      ; if (rax < rdx)
	jl  .end_while10                                  ;  goto .end_while10
;   action-10

	mov rax, qword [b]                                ; rax = b 
	push rax                                          ; rax => stack
	mov rdx, qword [b]                                ; rdx = b 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi ; number operator 14 
	push rax                                          ; rax => stack

	mov rax, 4                                        ; rax = 4 
	push rax                                          ; rax => stack
	mov rdx, qword [a]                                ; rdx = a 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi ; number operator 16 
	push rax                                          ; rax => stack
	mov rdx, qword [c]                                ; rdx = c 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi
	mov rdx, rax                                      ; rdx = rax ; number operator 16 
	pop rax                                           ; rax <= stack
	sub rax, rdx                                      ; rax -= rdx ; number operator 16 
	mov [Discriminant], rax                           ; Discriminant = rax  ; number operator 16 

	mov rax, -1                                       ; rax = -1 
	push rax                                          ; rax => stack

	mov rax, qword [Discriminant]                     ; rax = Discriminant 

	cvtsi2sd xmm0, rax                                ; xmm0 = (double) rax
	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)
	cvtsd2si rdx, xmm1                                ; rdx  = xmm1 ; number operator 21 
	pop rax                                           ; rax <= stack
	sub rax, rdx                                      ; rax -= rdx ; number operator 21 
	push rax                                          ; rax => stack

	mov rax, 2                                        ; rax = 2 
	push rax                                          ; rax => stack
	mov rdx, qword [a]                                ; rdx = a 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi
	mov rdx, rax                                      ; rdx = rax ; number operator 22 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	cqo                                               ; rdx = 0
	idiv rdi                                          ; rax = rax:rdx / rdi, rdx = rax:rdx / rdi ; number operator 22 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 22 

	mov rax, -1                                       ; rax = -1 
	push rax                                          ; rax => stack

	mov rax, qword [Discriminant]                     ; rax = Discriminant 

	cvtsi2sd xmm0, rax                                ; xmm0 = (double) rax
	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)
	cvtsd2si rdx, xmm1                                ; rdx  = xmm1 ; number operator 27 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 27 
	push rax                                          ; rax => stack

	mov rax, 2                                        ; rax = 2 
	push rax                                          ; rax => stack
	mov rdx, qword [a]                                ; rdx = a 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi
	mov rdx, rax                                      ; rdx = rax ; number operator 28 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	cqo                                               ; rdx = 0
	idiv rdi                                          ; rax = rax:rdx / rdi, rdx = rax:rdx / rdi ; number operator 28 
	mov [second_answ], rax                            ; second_answ = rax  ; number operator 28 

	mov rax, qword [ntimes]                           ; rax = ntimes 
	push rax                                          ; rax => stack
	mov rdx, 1                                        ; rdx = 1 
	pop rax                                           ; rax <= stack
	sub rax, rdx                                      ; rax -= rdx ; number operator 31 
	mov [ntimes], rax                                 ; ntimes = rax  ; number operator 31  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 32 
	jmp near .start_while10                           ;  goto .start_while10

.end_while10:

;---end-while-10---------------------------------------------------------------------------------- ; number operator 32  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 33 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

a: dq 0
b: dq 0
c: dq 0
ntimes: dq 0
Discriminant: dq 0
first_answ: dq 0
second_answ: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
