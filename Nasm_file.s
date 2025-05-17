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

my_main:                                              ; it is definition of my_main  ; number operator 3 

	call NoFactorial                                  ; NoFactorial (); ; number operator 5 

	mov rax, 7                                        ; rax = 7 

	call _my_print                                    ; print (eax) ; number operator 7 

	call _my_hlt                                      ; exit (0) ; number operator 9  ; number operator 10  ; number operator 10  ; number operator 10  ; number operator 10  ; number operator 10 

;----------------------------------------------------------------------------------------
;	NoFactorial:
;----------------------------------------------------------------------------------------

NoFactorial:                                          ; it is definition of NoFactorial  ; number operator 13 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 15 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 17  ; number operator 18  ; number operator 18  ; number operator 18  ; number operator 18  ; number operator 19  ; number operator 19  ; number operator 19 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
