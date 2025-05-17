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

	call _my_input                                    ; input(a); rax = input 
	mov [a], rax                                      ; [a] = rax  ; number operator 5 

	call _my_input                                    ; input(b); rax = input 
	mov [b], rax                                      ; [b] = rax  ; number operator 7 

	call _my_input                                    ; input(c); rax = input 
	mov [c], rax                                      ; [c] = rax  ; number operator 9 
;---start-if-11-----------------------------------------------------------------------------------
;   test-11

	mov rax, [a]                                      ; rax = a 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 13 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 13 
	test rax, rax                                     ;  if (rax = 0)
	je  .end_if11                                     ;  goto .end_if11
;   action-11

	call CountDiskriminant                            ; CountDiskriminant (); ; number operator 15 

	call _my_hlt                                      ; exit (0) ; number operator 17  ; number operator 18  ; number operator 18  ; number operator 18 

.end_if11:

;---end-if-11------------------------------------------------------------------------------------- ; number operator 18 
;---start-if-20-----------------------------------------------------------------------------------
;   test-20

	mov rax, [a]                                      ; rax = a 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 21 
	test rax, rax                                     ;  if (rax = 0)
	je  .end_if20                                     ;  goto .end_if20
;   action-20

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 23 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 28 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 28 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 28 
	mov [second_answ], rax                            ; second_answ = rax  ; number operator 28 

	mov rax, 2                                        ; rax = 2 

	call _my_print                                    ; print (eax) ; number operator 30 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 32 

	mov rax, [second_answ]                            ; rax = second_answ 

	call _my_print                                    ; print (eax) ; number operator 34 

	call _my_hlt                                      ; exit (0) ; number operator 36  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 37  ; number operator 37 

.end_if20:

;---end-if-20------------------------------------------------------------------------------------- ; number operator 37 
;---start-if-39-----------------------------------------------------------------------------------
;   test-39

	mov rax, [a]                                      ; rax = a 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 40 
	test rax, rax                                     ;  if (rax = 0)
	je  .end_if39                                     ;  goto .end_if39
;   action-39
;---start-if-42-----------------------------------------------------------------------------------
;   test-42

	mov rax, [c]                                      ; rax = c 
	mov rdx, 0                                        ; rdx = 0 
	cmp rax, rdx                                      ; if (rax > rdx)
	jb  .end_if42                                     ;  goto .end_if42
;   action-42

	mov rax, 0                                        ; rax = 0 

	call _my_print                                    ; print (eax) ; number operator 44 

	call _my_hlt                                      ; exit (0) ; number operator 46  ; number operator 47  ; number operator 47  ; number operator 47 

.end_if42:

;---end-if-42------------------------------------------------------------------------------------- ; number operator 47 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 53 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 53 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 53 

	cvtsi2sd xmm0, rax                                ; xmm0 = (double) rax
	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)
	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 53 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 53 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 57 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 61 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 61 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 61 

	cvtsi2sd xmm0, rax                                ; xmm0 = (double) rax
	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)
	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 61 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 61 
	mov [second_answ], rax                            ; second_answ = rax  ; number operator 61 

	mov rax, 2                                        ; rax = 2 

	call _my_print                                    ; print (eax) ; number operator 63 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 65 

	mov rax, [second_answ]                            ; rax = second_answ 

	call _my_print                                    ; print (eax) ; number operator 67 

	call _my_hlt                                      ; exit (0) ; number operator 69  ; number operator 70  ; number operator 70  ; number operator 70  ; number operator 70  ; number operator 70  ; number operator 70  ; number operator 70  ; number operator 70 

.end_if39:

;---end-if-39------------------------------------------------------------------------------------- ; number operator 70 
;---start-if-72-----------------------------------------------------------------------------------
;   test-72

	mov rax, [b]                                      ; rax = b 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 73 
	test rax, rax                                     ;  if (rax = 0)
	je  .end_if72                                     ;  goto .end_if72
;   action-72

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 78 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 78 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 78 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 78 

	mov rax, 1                                        ; rax = 1 

	call _my_print                                    ; print (eax) ; number operator 80 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 82 

	call _my_hlt                                      ; exit (0) ; number operator 84  ; number operator 85  ; number operator 85  ; number operator 85  ; number operator 85  ; number operator 85 

.end_if72:

;---end-if-72------------------------------------------------------------------------------------- ; number operator 85 
;---start-if-87-----------------------------------------------------------------------------------
;   test-87

	mov rax, [c]                                      ; rax = c 
	test rax, rax                                     ;  if (rax = 0)
	je  .end_if87                                     ;  goto .end_if87
;   action-87

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 89 

	mov rax, 0                                        ; rax = 0 

	call _my_print                                    ; print (eax) ; number operator 91 

	call _my_hlt                                      ; exit (0) ; number operator 93  ; number operator 94  ; number operator 94  ; number operator 94  ; number operator 94 

.end_if87:

;---end-if-87------------------------------------------------------------------------------------- ; number operator 94 
;---start-if-96-----------------------------------------------------------------------------------
;   test-96

	mov rax, [a]                                      ; rax = a 
	test rax, rax                                     ;  if (rax = 0)
	je  .end_if96                                     ;  goto .end_if96
;   action-96

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 98 

	mov rax, 1                                        ; rax = 1 

	call _my_print                                    ; print (eax) ; number operator 100 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 102 

	call _my_hlt                                      ; exit (0) ; number operator 104  ; number operator 105  ; number operator 105  ; number operator 105  ; number operator 105  ; number operator 105 

.end_if96:

;---end-if-96------------------------------------------------------------------------------------- ; number operator 105 
;---start-if-107-----------------------------------------------------------------------------------
;   test-107

	mov rax, [b]                                      ; rax = b 
	test rax, rax                                     ;  if (rax = 0)
	je  .end_if107                                    ;  goto .end_if107
;   action-107

	mov rax, 0                                        ; rax = 0 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 109 

	mov rax, 1                                        ; rax = 1 

	call _my_print                                    ; print (eax) ; number operator 111 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 113 

	call _my_hlt                                      ; exit (0) ; number operator 115  ; number operator 116  ; number operator 116  ; number operator 116  ; number operator 116  ; number operator 116 

.end_if107:

;---end-if-107------------------------------------------------------------------------------------- ; number operator 116 

	mov rax, 8                                        ; rax = 8 

	call _my_print                                    ; print (eax) ; number operator 118  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119  ; number operator 119 

;--------------------------------------------------------------------------------------------------
;	CountDiskriminant:
;--------------------------------------------------------------------------------------------------

CountDiskriminant:                                    ; it is definition of CountDiskriminant  ; number operator 122 

	mov rax, [b]                                      ; rax = b 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 126 

	mov rax, 4                                        ; rax = 4 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 128 
	mov rdx, [c]                                      ; rdx = c 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 128 
	sub rax, rdx                                      ; rax -= rdx ; number operator 128 
	mov [Diskriminant], rax                           ; Diskriminant = rax  ; number operator 128 

	mov rax, [Diskriminant]                           ; rax = Diskriminant 

	call _my_print                                    ; print (eax) ; number operator 130 
;---start-if-132-----------------------------------------------------------------------------------
;   test-132

	mov rax, [Diskriminant]                           ; rax = Diskriminant 
	mov rdx, 0                                        ; rdx = 0 
	cmp rax, rdx                                      ; if (rax < rdx)
	ja  .end_if132                                    ;  goto .end_if132
;   action-132

	mov rax, 0                                        ; rax = 0 

	call _my_print                                    ; print (eax) ; number operator 134 

	call _my_hlt                                      ; exit (0) ; number operator 136  ; number operator 137  ; number operator 137  ; number operator 137 

.end_if132:

;---end-if-132------------------------------------------------------------------------------------- ; number operator 137 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 143 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 143 

	mov rax, [Diskriminant]                           ; rax = Diskriminant 

	cvtsi2sd xmm0, rax                                ; xmm0 = (double) rax
	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)
	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 144 
	sub rax, rdx                                      ; rax -= rdx ; number operator 144 

	mov rax, 2                                        ; rax = 2 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 145 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 145 
	mov [first_answ], rax                             ; first_answ = rax  ; number operator 145 

	mov rax, 0                                        ; rax = 0 
	mov rdx, 1                                        ; rdx = 1 
	sub rax, rdx                                      ; rax -= rdx ; number operator 151 
	mov rdx, [b]                                      ; rdx = b 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 151 

	mov rax, [Diskriminant]                           ; rax = Diskriminant 

	cvtsi2sd xmm0, rax                                ; xmm0 = (double) rax
	sqrtsd xmm1, xmm0                                 ; xmm1 = sqrt (xmm0)
	cvtsd2si rax, xmm1                                ; rax  = xmm1 ; number operator 152 
	add rax, rdx                                      ; rax += rdx ; number operator 152 

	mov rax, 2                                        ; rax = 2 
	mov rdx, [a]                                      ; rdx = a 
	mov rdi, rdx                                      ; rdi = rdx
	mul edi                                           ; edx:eax = eax * edi ; number operator 153 
	mov rdi, rdx                                      ; rdi = rdx
	xor rdx, rdx                                      ; rdx = 0
	div edi                                           ; eax = eax:edx / edi, edx = eax:edx / edi ; number operator 153 
	mov [second_answ], rax                            ; second_answ = rax  ; number operator 153 

	mov rax, 2                                        ; rax = 2 

	call _my_print                                    ; print (eax) ; number operator 155 

	mov rax, [first_answ]                             ; rax = first_answ 

	call _my_print                                    ; print (eax) ; number operator 157 

	mov rax, [second_answ]                            ; rax = second_answ 

	call _my_print                                    ; print (eax) ; number operator 159  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 160  ; number operator 161  ; number operator 161  ; number operator 161 

call _my_hlt                                          ; exit (0)
;--------------------------------------------------------------------------------------------------

section .data

a: dq 0
b: dq 0
c: dq 0
first_answ: dq 0
second_answ: dq 0
Diskriminant: dq 0
;--------------------------------------------------------------------------------------------------

section .note.GNU-stack
