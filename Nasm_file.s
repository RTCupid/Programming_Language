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

	mov rax, [Process]                                ; rax = Process 

	push rax                                          ; rax => stack, make stack frame;

	call Process                                      ; Process (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 9 

	mov rax, [NoFactorial]                            ; rax = NoFactorial 

	push rax                                          ; rax => stack, make stack frame;

	call NoFactorial                                  ; NoFactorial (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 11 

	mov rax, 7                                        ; rax = 7 

	call _my_print                                    ; print (eax) ; number operator 13 

	call _my_hlt                                      ; exit (0) ; number operator 15  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16 

;--------------------------------------------------------------------------------------------------
;	NoFactorial:
;--------------------------------------------------------------------------------------------------

NoFactorial:                                          ; it is definition of NoFactorial  ; number operator 19 

	mov rax, 334                                      ; rax = 334 

	call _my_print                                    ; print (eax) ; number operator 21 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 23  ; number operator 24  ; number operator 24  ; number operator 24  ; number operator 24 

;--------------------------------------------------------------------------------------------------
;	Process:
;--------------------------------------------------------------------------------------------------

Process:                                              ; it is definition of Process  ; number operator 27 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 29 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 31  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 32  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 33 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

argument: dq 0
not_argument: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
