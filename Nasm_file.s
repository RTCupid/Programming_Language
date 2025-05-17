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
	mov [x], rax; x = rax
;number operator 5 
	mov rax, 20
	mov [y], rax; y = rax
;number operator 7 
	mov rax, 3
	mov [z], rax; z = rax
;number operator 9 
	mov rax, [x]; x

	mov rdx, [y]; y

	add rax, rdx;number operator 12 
	mov [sum], rax; sum = rax
;number operator 12 
	mov rax, [sum]; sum


	call _my_print;number operator 14 
	mov rax, [x]; x

	mov rdx, [z]; z

	mov rdi, rdx; rdi = rdx
	mul edi;number operator 17 
	mov [mult], rax; mult = rax
;number operator 17 
	mov rax, [mult]; mult


	call _my_print;number operator 19 
	mov rax, [sum]; sum

	mov rdx, [z]; z

	mov rdi, rdx; rdi = rdx
	xor rdx, rdx; rdx = 0
	div edi;number operator 22 
	mov [divi], rax; divi = rax
;number operator 22 
	mov rax, [divi]; divi


	call _my_print;number operator 24 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 26 ;number operator 26 
	call _my_hlt
;--------------------------------------------------------------------------------------------------

section .data

x: TIMES 64 db 0
y: TIMES 64 db 0
z: TIMES 64 db 0
sum: TIMES 64 db 0
mult: TIMES 64 db 0
divi: TIMES 64 db 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
