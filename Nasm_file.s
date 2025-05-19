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

	                                                  ; [rbp + 8] = function's argument

	mov rax, 1                                        ; rax = 1 
	mov [first_argument], rax                         ; first_argument = rax  ; number operator 5 

	mov rax, [first_argument]                         ; rax = first_argument 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Function                                     ; Function (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 7 

	call _my_hlt                                      ; exit (0) ; number operator 9  ; number operator 10  ; number operator 10  ; number operator 10  ; number operator 10  ; number operator 10 

;--------------------------------------------------------------------------------------------------
;	Function:
;	Entry: arg = [rbp + 8]
;	Entry: adress to return = [rbp]
;--------------------------------------------------------------------------------------------------

Function:                                             ; it is definition of Function  ; number operator 13 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 8] = function's argument

	mov rax, [rbp + 8]                                ; rax = arg 
	push rax                                          ; rax => stack
	mov rdx, 1000                                     ; rdx = 1000 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 16 
	mov [arg], rax                                    ; arg = rax  ; number operator 16 

	mov rax, [rbp + 8]                                ; rax = arg 

	call _my_print                                    ; print (eax) ; number operator 18 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 20  ; number operator 21  ; number operator 21  ; number operator 21  ; number operator 21  ; number operator 21  ; number operator 22  ; number operator 22  ; number operator 22 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

first_argument: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
