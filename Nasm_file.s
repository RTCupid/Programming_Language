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

	                                                  ; [rbp + 8] = function's argument

	mov rax, [utyutyu]                                ; rax = utyutyu 

	call _my_print                                    ; print (eax) ; number operator 7 

	call _my_input                                    ; input(argument); rax = input 
	mov [argument], rax                               ; [argument] = rax  ; number operator 9 

	mov rax, [argument]                               ; rax = argument 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Function                                     ; Function (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 11 

	mov rax, [argument]                               ; rax = argument 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Summator                                     ; Summator (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 13 

	call _my_hlt                                      ; exit (0) ; number operator 15  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16  ; number operator 16 

;--------------------------------------------------------------------------------------------------
;	Function:
;--------------------------------------------------------------------------------------------------

Function:                                             ; it is definition of Function  ; number operator 19 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 8] = function's argument

	mov rax, [fact]                                   ; rax = fact 

	call _my_print                                    ; print (eax) ; number operator 21 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 23  ; number operator 24  ; number operator 24  ; number operator 24  ; number operator 24 

;--------------------------------------------------------------------------------------------------
;	Summator:
;--------------------------------------------------------------------------------------------------

Summator:                                             ; it is definition of Summator  ; number operator 27 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 8] = function's argument

	mov rax, [sum]                                    ; rax = sum 
	push rax                                          ; rax => stack
	mov rdx, 1                                        ; rdx = 1 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 30 

	call _my_print                                    ; print (eax) ; number operator 30 

	mov rax, 0                                        ; rax = 0 

	ret                                               ; return; ; number operator 32  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 33  ; number operator 34  ; number operator 34  ; number operator 34  ; number operator 34  ; number operator 34 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

utyutyu: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
