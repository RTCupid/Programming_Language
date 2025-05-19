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

	call _my_input                                    ; input(argument); rax = input 
	mov [argument], rax                               ; [argument] = rax  ; number operator 9 

	mov rax, 10                                       ; rax = 10 
	mov [fact], rax                                   ; fact = rax  ; number operator 11 

	mov rax, [fact]                                   ; rax = fact 

	call _my_print                                    ; print (eax) ; number operator 13 

	mov rax, [argument]                               ; rax = argument 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Function                                     ; Function (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 15 

	mov rax, [argument]                               ; rax = argument 

	sub rsp, 8                                        ; reserved 8 byte for argument

	mov [rsp], rax                                    ; rax => [rsp], make stack frame;

	call Summator                                     ; Summator (rax);

	add rsp, 8                                        ; clean stack frame; ; number operator 17 

	call _my_hlt                                      ; exit (0) ; number operator 19  ; number operator 20  ; number operator 20  ; number operator 20  ; number operator 20  ; number operator 20  ; number operator 20  ; number operator 20  ; number operator 20  ; number operator 20 

;--------------------------------------------------------------------------------------------------
;	Function:
;	Entry: fact = [rbp + 8]
;--------------------------------------------------------------------------------------------------

Function:                                             ; it is definition of Function  ; number operator 23 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 8] = function's argument

	mov rax, [fact]                                   ; rax = fact 

	call _my_print                                    ; print (eax) ; number operator 25 

	mov rax, 0                                        ; rax = 0 

	mov rsp, rbp                                      ; rsp = rbp, back old value of rsp

	ret                                               ; return; ; number operator 27  ; number operator 28  ; number operator 28  ; number operator 28  ; number operator 28 

;--------------------------------------------------------------------------------------------------
;	Summator:
;	Entry: sum = [rbp + 8]
;--------------------------------------------------------------------------------------------------

Summator:                                             ; it is definition of Summator  ; number operator 31 

	mov rbp, rsp                                      ; rbp = rsp, save old value of rsp

	                                                  ; [rbp] = address for return

	                                                  ; [rbp + 8] = function's argument

	mov rax, [sum]                                    ; rax = sum 
	push rax                                          ; rax => stack
	mov rdx, 1                                        ; rdx = 1 
	pop rax                                           ; rax <= stack
	add rax, rdx                                      ; rax += rdx ; number operator 34 

	call _my_print                                    ; print (eax) ; number operator 34 

	mov rax, 0                                        ; rax = 0 

	mov rsp, rbp                                      ; rsp = rbp, back old value of rsp

	ret                                               ; return; ; number operator 36  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 38  ; number operator 38  ; number operator 38  ; number operator 38  ; number operator 38 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

utyutyu: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
