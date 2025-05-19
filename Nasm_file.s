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
;	my_main:
;--------------------------------------------------------------------------------------------------

my_main:                                              ; it is definition of my_main  ; number operator 5 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, [utyutyu]                                ; rax = utyutyu 

	call _my_print                                    ; print (eax) ; number operator 7 

	mov rax, 0                                        ; rax = 0 
	mov [first_argument], rax                         ; first_argument = rax  ; number operator 9 

	mov rax, [first_argument]                         ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 11 

	mov rax, [utyutyu]                                ; rax = utyutyu 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Function                                     ; Function (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 13 

	mov rax, [first_argument]                         ; rax = first_argument 

	call _my_print                                    ; print (eax) ; number operator 15 

	call _my_hlt                                      ; exit (0) ; number operator 17  ; number operator 18  ; number operator 18  ; number operator 18  ; number operator 18  ; number operator 18  ; number operator 18  ; number operator 18  ; number operator 18 

;--------------------------------------------------------------------------------------------------
;	Function:
;--------------------------------------------------------------------------------------------------

Function:                                             ; it is definition of Function  ; number operator 21 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	mov rax, 1                                        ; rax = 1 
	mov [first_argument], rax                         ; first_argument = rax  ; number operator 23 

	mov rax, 0                                        ; rax = 0 

	mov rsp, rbp                                      ; rsp = rbp, back old value of rsp

	ret                                               ; return; ; number operator 25  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 26  ; number operator 27  ; number operator 27  ; number operator 27  ; number operator 27 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

utyutyu: dq 0
utyutyu: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
