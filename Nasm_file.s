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
	mov [first_argument], rax                         ; first_argument = rax  ; number operator 5 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 7 

	call Function                                     ; Function (rax); ; number operator 9 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 11 

	call _my_hlt                                      ; exit (0) ; number operator 13  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14 

;--------------------------------------------------------------------------------------------------
;	Function:
;--------------------------------------------------------------------------------------------------

Function:                                             ; it is definition of Function  ; number operator 17 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, 1                                        ; rax = 1 
	mov [first_argument], rax                         ; first_argument = rax  ; number operator 19 

	mov rax, 5                                        ; rax = 5 
	mov [cool_variable], rax                          ; cool_variable = rax  ; number operator 21 

	call Second_Function                              ; Second_Function (rax); ; number operator 23 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = cool_variable 
	push rax                                          ; rax => stack
	mov rdx, 66                                       ; rdx = 66 
	pop rax                                           ; rax <= stack
	mov rdi, rdx                                      ; rdi = rdx
	imul rdi                                          ; rdx:rax = rax * rdi ; number operator 26 
	mov [answer], rax                                 ; answer = rax  ; number operator 26 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = answer 

	mov rsp, rbp                                      ; rsp = rbp, back old value of rsp

	ret                                               ; return; ; number operator 28  ; number operator 29  ; number operator 29  ; number operator 29  ; number operator 29  ; number operator 29  ; number operator 29  ; number operator 29 

;--------------------------------------------------------------------------------------------------
;	Second_Function:
;--------------------------------------------------------------------------------------------------

Second_Function:                                      ; it is definition of Second_Function  ; number operator 32 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, 222                                      ; rax = 222 
	mov [answer], rax                                 ; answer = rax  ; number operator 34 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = answer 

	call _my_print                                    ; print (eax) ; number operator 36  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 38  ; number operator 38  ; number operator 38  ; number operator 38 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
