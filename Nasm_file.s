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

	mov rax, 4                                        ; rax = 4 
	mov [x], rax                                      ; x = rax  ; number operator 5 

	mov rax, 7                                        ; rax = 7 
	mov [y], rax                                      ; y = rax  ; number operator 7 

	mov rax, 90                                       ; rax = 90 
	mov [z], rax                                      ; z = rax  ; number operator 9 

	mov rax, [x]                                      ; rax = x 
	push rax                                          ; rax => stack

	mov rax, 4                                        ; rax = 4 
	push rax                                          ; rax => stack
	mov rdx, [y]                                      ; rdx = y 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx
	mov rdx, rax                                      ; rdx = rax ; number operator 14 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 14 
	push rax                                          ; rax => stack
	mov rdx, [z]                                      ; rdx = z 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 14 
	mov [advanced_sum], rax                           ; advanced_sum = rax  ; number operator 14 

	mov rax, [advanced_sum]                           ; rax = advanced_sum 

	call _my_print                                    ; print (eax) ; number operator 16 

	mov rax, 16                                       ; rax = 16 
	mov [a], rax                                      ; a = rax  ; number operator 18 

	mov rax, [x]                                      ; rax = x 
	push rax                                          ; rax => stack
	mov rdx, [a]                                      ; rdx = a 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 23 
	push rax                                          ; rax => stack
	mov rdx, [z]                                      ; rdx = z 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 23 
	push rax                                          ; rax => stack
	mov rdx, [a]                                      ; rdx = a 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 23 
	mov [advanced_sqrt], rax                          ; advanced_sqrt = rax  ; number operator 23 

	mov rax, [advanced_sqrt]                          ; rax = advanced_sqrt 

	call _my_print                                    ; print (eax) ; number operator 25  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 27  ; number operator 27 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

x: dq 0
y: dq 0
z: dq 0
advanced_sum: dq 0
a: dq 0
advanced_sqrt: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
