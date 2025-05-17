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
	mov [1], rax; x = rax
;number operator 5 
	mov rax, 20
	mov [2], rax; y = rax
;number operator 7 
	mov rax, 3
	mov [3], rax; z = rax
;number operator 9 
	mov rax, [1]; x

	mov rdx, [2]; y

	add rax, rdx;number operator 12 
	mov [4], rax; sum = rax
;number operator 12 
	mov rax, [4]; sum


	call _my_print;number operator 14 
	mov rax, [1]; x

	mov rdx, [3]; z

	mul rax, rdx;number operator 17 
	mov [5], rax; mult = rax
;number operator 17 
	mov rax, [5]; mult


	call _my_print;number operator 19 
	mov rax, [4]; sum

	mov rdx, [3]; z

	div rax, rdx;number operator 22 
	mov [6], rax; divi = rax
;number operator 22 
	mov rax, [6]; divi


	call _my_print;number operator 24 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 25 ;number operator 26 ;number operator 26 
	call _my_hlt

section .note.GNU-stack

my_main: equ 64
x: equ 64
y: equ 64
z: equ 64
sum: equ 64
mult: equ 64
divi: equ 64