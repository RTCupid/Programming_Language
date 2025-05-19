;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

%INCLUDE "stdlib.s"

section .text

_start:

	and rsp, -16

	mov rax, 19                                       ; rax = 19 
	mov [utyutyu], rax                                ; utyutyu = rax  ; number operator 2 

;--------------------------------------------------------------------------------------------------
;	fictive:
;--------------------------------------------------------------------------------------------------

fictive:                                              ; it is definition of fictive  ; number operator 5 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, 5                                        ; rax = 5 

	call _my_print                                    ; print (eax) ; number operator 7  ; number operator 8  ; number operator 8  ; number operator 8 

;--------------------------------------------------------------------------------------------------
;	my_main:
;--------------------------------------------------------------------------------------------------

my_main:                                              ; it is definition of my_main  ; number operator 11 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, [utyutyu]                                ; rax = utyutyu 

	call _my_print                                    ; print (eax) ; number operator 13 

	mov rax, 0                                        ; rax = 0 
	mov [first_argument], rax                         ; first_argument = rax  ; number operator 15 

	mov rax, [first_argument]                         ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 17 

	mov rax, [utyutyu]                                ; rax = utyutyu 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Function                                     ; Function (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 19 

	mov rax, [first_argument]                         ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 21 

	call _my_hlt                                      ; exit (0) ; number operator 23  ; number operator 24  ; number operator 24  ; number operator 24  ; number operator 24  ; number operator 24  ; number operator 24  ; number operator 24  ; number operator 24 

;--------------------------------------------------------------------------------------------------
;	Function:
;--------------------------------------------------------------------------------------------------

Function:                                             ; it is definition of Function  ; number operator 27 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, 1                                        ; rax = 1 
	mov [first_argument], rax                         ; first_argument = rax  ; number operator 29 

	mov rax, 0                                        ; rax = 0 

	mov rsp, rbp                                      ; rsp = rbp, back old value of rsp

	ret                                               ; return; ; number operator 31  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 33 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

utyutyu: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
