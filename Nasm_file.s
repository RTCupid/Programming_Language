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

	mov rax, [first_argument]                         ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 7 

	mov rax, [my_main]                                ; rax = my_main 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Function                                     ; Function (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 9 

	mov rax, [first_argument]                         ; rax = first_argument 

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

	mov rax, 0                                        ; rax = 0 

	mov rsp, rbp                                      ; rsp = rbp, back old value of rsp

	ret                                               ; return; ; number operator 21  ; number operator 22  ; number operator 22  ; number operator 22  ; number operator 22  ; number operator 23  ; number operator 23  ; number operator 23 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
