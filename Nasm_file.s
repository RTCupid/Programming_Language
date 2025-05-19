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

	call _my_input                                    ; input(first_argument); rax = input 
	mov [first_argument], rax                         ; [first_argument] = rax  ; number operator 5 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 7 

	mov rcx, 8 * 0                                    ; rcx = 8 * 0 

	mov rax, [ebp + rcx]                              ; rax = first_argument 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Function                                     ; Function (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 9 

	call _my_hlt                                      ; exit (0) ; number operator 11  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 12 

;--------------------------------------------------------------------------------------------------
;	Function:
;	Entry: arg = [rbp + 8]
;--------------------------------------------------------------------------------------------------

Function:                                             ; it is definition of Function  ; number operator 15 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 8] = function's argument

	mov rax, [arg]                                    ; rax = arg 
	push rax                                          ; rax => stack
	mov rdx, 2                                        ; rdx = 2 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 18 
	mov [arg], rax                                    ; arg = rax  ; number operator 18 

	mov rax, [arg]                                    ; rax = arg 

	call _my_print                                    ; print (eax) ; number operator 20 

	mov rax, 0                                        ; rax = 0 

	mov rsp, rbp                                      ; rsp = rbp, back old value of rsp

	ret                                               ; return; ; number operator 22  ; number operator 23  ; number operator 23  ; number operator 23  ; number operator 23  ; number operator 23  ; number operator 24  ; number operator 24  ; number operator 24 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

arg: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
