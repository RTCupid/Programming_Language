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

	mov rax, [abc]                                    ; rax = abc 
	mov [sum], rax                                    ; sum = rax  ; number operator 5 

	mov rax, [sum]                                    ; rax = sum 

	call _my_print                                    ; print (eax) ; number operator 7 

	mov rax, [utyutyu]                                ; rax = utyutyu 

	call _my_print                                    ; print (eax) ; number operator 9 

	mov rax, [mash]                                   ; rax = mash 

	call _my_print                                    ; print (eax) ; number operator 11  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 12  ; number operator 13  ; number operator 13 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

sum: dq 0
abc: dq 0
utyutyu: dq 0
mash: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
