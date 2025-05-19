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

	mov rax, 1                                        ; rax = 1  ; number operator 5 

	call (null)                                       ; (null) (rax); ; number operator 7 

	call _my_hlt                                      ; exit (0) ; number operator 9  ; number operator 10  ; number operator 10  ; number operator 10  ; number operator 10  ; number operator 10 

;--------------------------------------------------------------------------------------------------
;	(null):
;--------------------------------------------------------------------------------------------------

(null):                                               ; it is definition of (null)  ; number operator 13 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 8] = function's argument
	push rax                                          ; rax => stack
	mov rdx, 1000                                     ; rdx = 1000 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 16  ; number operator 16 

	call _my_print                                    ; print (eax) ; number operator 18 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 20  ; number operator 21  ; number operator 21  ; number operator 21  ; number operator 21  ; number operator 21  ; number operator 22  ; number operator 22  ; number operator 22 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
