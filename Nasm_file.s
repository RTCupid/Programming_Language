;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

%INCLUDE "stdlib.s"

section .text

_start:

	and rsp, -16

	call _my_input                                    ; input(a); rax = input 
	mov [a], rax                                      ; [a] = rax  ; number operator 2 

	call _my_input                                    ; input(b); rax = input 
	mov [b], rax                                      ; [b] = rax  ; number operator 4 

	call _my_input                                    ; input(c); rax = input 
	mov [c], rax                                      ; [c] = rax  ; number operator 6 
;---start-if-8-----------------------------------------------------------------------------------
;   test-8

	mov rax, [a]                                      ; rax = a 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 10 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 10 
	test rax, rax                                     ;  if (rax = 0)
	je  end_if8                                       ;  goto end_if8
;   action-8

	mov rax, [b]                                      ; rax = b 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 14 

	mov rax, 4                                        ; rax = 4 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 16 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 16 
	sub rax, rdx                                      ; rax -= rdx ; number operator 16 
	mov [Diskriminant], rax                           ; Diskriminant = rax  ; number operator 16 

	mov rax, [Diskriminant]                           ; rax = Diskriminant 

	call _my_print                                    ; print (eax) ; number operator 18 
;---start-if-20-----------------------------------------------------------------------------------
;   test-20

	mov rax, [Diskriminant]                           ; rax = Diskriminant 

	mov rax, 0                                        ; rax = 0 
	jb  end_if20                                      ;  goto end_if20
;   action-20

	mov rax, 0                                        ; rax = 0 

	call _my_print                                    ; print (eax) ; number operator 22 

	call _my_hlt                                      ; exit (0) ; number operator 24  ; number operator 25  ; number operator 25  ; number operator 25 
end_if20:
;---end-if-20------------------------------------------------------------------------------------- ; number operator 25 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 31 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 31 

	mov rax, [Diskriminant]                           ; rax = Diskriminant 

	movq xmm0, rax                                    ; xmm0 = rax

	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)

	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 32 
	sub rax, rdx                                      ; rax -= rdx ; number operator 32 

	mov rax, 2                                        ; rax = 2 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 33 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 33 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 33 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 39 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 39 

	mov rax, [Diskriminant]                           ; rax = Diskriminant 

	movq xmm0, rax                                    ; xmm0 = rax

	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)

	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 40 
	add rax, rdx                                      ; rax += rdx ; number operator 40 

	mov rax, 2                                        ; rax = 2 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 41 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 41 
	mov [second_answ], rax                            ; second_answ = rax  ; number operator 41 

	mov rax, 2                                        ; rax = 2 

	call _my_print                                    ; print (eax) ; number operator 43 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 45 

	mov rax, [second_answ]                            ; rax = second_answ 

	call _my_print                                    ; print (eax) ; number operator 47 

	call _my_hlt                                      ; exit (0) ; number operator 49  ; number operator 50  ; number operator 50  ; number operator 50  ; number operator 50  ; number operator 50  ; number operator 50  ; number operator 50  ; number operator 50  ; number operator 50  ; number operator 50 
end_if8:
;---end-if-8------------------------------------------------------------------------------------- ; number operator 50 
;---start-if-52-----------------------------------------------------------------------------------
;   test-52

	mov rax, [a]                                      ; rax = a 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 53 
	test rax, rax                                     ;  if (rax = 0)
	je  end_if52                                      ;  goto end_if52
;   action-52

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 55 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 60 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 60 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 60 
	mov [second_answ], rax                            ; second_answ = rax  ; number operator 60 

	mov rax, 2                                        ; rax = 2 

	call _my_print                                    ; print (eax) ; number operator 62 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 64 

	mov rax, [second_answ]                            ; rax = second_answ 

	call _my_print                                    ; print (eax) ; number operator 66 

	call _my_hlt                                      ; exit (0) ; number operator 68  ; number operator 69  ; number operator 69  ; number operator 69  ; number operator 69  ; number operator 69  ; number operator 69  ; number operator 69 
end_if52:
;---end-if-52------------------------------------------------------------------------------------- ; number operator 69 
;---start-if-71-----------------------------------------------------------------------------------
;   test-71

	mov rax, [a]                                      ; rax = a 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 72 
	test rax, rax                                     ;  if (rax = 0)
	je  end_if71                                      ;  goto end_if71
;   action-71
;---start-if-74-----------------------------------------------------------------------------------
;   test-74

	mov rax, [c]                                      ; rax = c 

	mov rax, 0                                        ; rax = 0 
	ja  end_if74                                      ;  goto end_if74
;   action-74

	mov rax, 0                                        ; rax = 0 

	call _my_print                                    ; print (eax) ; number operator 76 

	call _my_hlt                                      ; exit (0) ; number operator 78  ; number operator 79  ; number operator 79  ; number operator 79 
end_if74:
;---end-if-74------------------------------------------------------------------------------------- ; number operator 79 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 85 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 85 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 85 

	movq xmm0, rax                                    ; xmm0 = rax

	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)

	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 85 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 85 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 89 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 93 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 93 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 93 

	movq xmm0, rax                                    ; xmm0 = rax

	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)

	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 93 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 93 
	mov [second_answ], rax                            ; second_answ = rax  ; number operator 93 

	mov rax, 2                                        ; rax = 2 

	call _my_print                                    ; print (eax) ; number operator 95 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 97 

	mov rax, [second_answ]                            ; rax = second_answ 

	call _my_print                                    ; print (eax) ; number operator 99 

	call _my_hlt                                      ; exit (0) ; number operator 101  ; number operator 102  ; number operator 102  ; number operator 102  ; number operator 102  ; number operator 102  ; number operator 102  ; number operator 102  ; number operator 102 
end_if71:
;---end-if-71------------------------------------------------------------------------------------- ; number operator 102 
;---start-if-104-----------------------------------------------------------------------------------
;   test-104

	mov rax, [b]                                      ; rax = b 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 105 
	test rax, rax                                     ;  if (rax = 0)
	je  end_if104                                     ;  goto end_if104
;   action-104

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 110 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 110 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 110 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 110 

	mov rax, 1                                        ; rax = 1 

	call _my_print                                    ; print (eax) ; number operator 112 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 114 

	call _my_hlt                                      ; exit (0) ; number operator 116  ; number operator 117  ; number operator 117  ; number operator 117  ; number operator 117  ; number operator 117 
end_if104:
;---end-if-104------------------------------------------------------------------------------------- ; number operator 117 
;---start-if-119-----------------------------------------------------------------------------------
;   test-119

	mov rax, [c]                                      ; rax = c 
	test rax, rax                                     ;  if (rax = 0)
	je  end_if119                                     ;  goto end_if119
;   action-119

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 121 

	mov rax, 0                                        ; rax = 0 

	call _my_print                                    ; print (eax) ; number operator 123 

	call _my_hlt                                      ; exit (0) ; number operator 125  ; number operator 126  ; number operator 126  ; number operator 126  ; number operator 126 
end_if119:
;---end-if-119------------------------------------------------------------------------------------- ; number operator 126 
;---start-if-128-----------------------------------------------------------------------------------
;   test-128

	mov rax, [a]                                      ; rax = a 
	test rax, rax                                     ;  if (rax = 0)
	je  end_if128                                     ;  goto end_if128
;   action-128

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 130 

	mov rax, 1                                        ; rax = 1 

	call _my_print                                    ; print (eax) ; number operator 132 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 134 

	call _my_hlt                                      ; exit (0) ; number operator 136  ; number operator 137  ; number operator 137  ; number operator 137  ; number operator 137  ; number operator 137 
end_if128:
;---end-if-128------------------------------------------------------------------------------------- ; number operator 137 
;---start-if-139-----------------------------------------------------------------------------------
;   test-139

	mov rax, [b]                                      ; rax = b 
	test rax, rax                                     ;  if (rax = 0)
	je  end_if139                                     ;  goto end_if139
;   action-139

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 141 

	mov rax, 1                                        ; rax = 1 

	call _my_print                                    ; print (eax) ; number operator 143 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 145 

	call _my_hlt                                      ; exit (0) ; number operator 147  ; number operator 148  ; number operator 148  ; number operator 148  ; number operator 148  ; number operator 148 
end_if139:
;---end-if-139------------------------------------------------------------------------------------- ; number operator 148 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 150  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151  ; number operator 151 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

a: dq 0
b: dq 0
c: dq 0
Diskriminant: dq 0
first_answ: dq 0
second_answ: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
