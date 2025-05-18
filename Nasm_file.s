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

	mov rax, 19                                       ; rax = 19 
	mov [argument], rax                               ; argument = rax  ; number operator 5 

	mov rax, 222                                      ; rax = 222 
	mov [not_argument], rax                           ; not_argument = rax  ; number operator 7 

	call Process                                      ; Process (); ; number operator 9 

	mov rax, 7                                        ; rax = 7 

	call _my_print                                    ; print (eax) ; number operator 11 

	call _my_hlt                                      ; exit (0) ; number operator 13  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14  ; number operator 14 

;--------------------------------------------------------------------------------------------------
;	Process:
;--------------------------------------------------------------------------------------------------

Process:                                              ; it is definition of Process  ; number operator 17 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 19 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 21  ; number operator 22  ; number operator 22  ; number operator 22  ; number operator 22  ; number operator 23  ; number operator 23  ; number operator 23 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

argument: dq 0
not_argument: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
