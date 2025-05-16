%ifndef STDLIB_S
%define STDLIB_S
;--------------------------------------------------------------------------------------------------
;                                  stdlib.s
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------

section  .text

;----------------------------------------------------------------------------------------
; _my_hlt - my function hlt for NASM
; Entry:    NONE
; Exit:     rdi - number of error
; Destroy:  rdi, rax
;----------------------------------------------------------------------------------------
_my_hlt:

    mov  rax, 0x3C                                  ; exit64 (rdi)
    xor  rdi, rdi                                   ; rdi = 0
    syscall                                         ; exit (0)

;----------------------------------------------------------------------------------------
; _my_input - my function input for NASM
; Entry:    NONE
; Exit:     rax = input number
; Destroy:  rax
;----------------------------------------------------------------------------------------
_my_input:

    ret

;----------------------------------------------------------------------------------------
; _my_print - my function to print dex number for NASM
; Entry:    rax = number to print
; Exit:     NONE
; Destroy: rdx, rax, rbx, r12, r13, r14, rsi, rdi
;----------------------------------------------------------------------------------------
_my_print:

    push rbx                                        ;------------------------------------
    push rbp                                        ;                                   |
    push r12                                        ;    Save                           |
    push r13                                        ;       Callee saved registers      |
    push r14                                        ;                                   |
    push r15                                        ;------------------------------------

;-----------handler-dex-number-----------------------------------------------------------

    xor  rdx, rdx                                   ; rdx = 0, rdx = index in buffer

    cmp  eax, 0                                     ; if (eax > 0) {
    jg   DexPositiveParam                           ;     goto DexPositiveParam }

    neg  eax                                        ; eax = -eax, find positive value of eax

    mov  rbx, '-'                                   ; rbx         = '-'
    mov  [Buffer], bl                               ; Buffer[rdx] = '-'
    inc  rdx                                        ; rdx++

DexPositiveParam:

    mov  r14, rdx                                   ; save old value rdx in r14

    mov  r12, 10                                    ; r12 = 10, factor for div

    xor  r13, r13                                   ; r13 = 0, r13 = counter of dex digits

NewDigitDex:

    xor  rdx, rdx                                   ; rdx = 0              -------------
                                                    ;             number - | rdx : rax |
                                                    ;                      -------------
    div  r12                                        ; rax = rdx / 10, rdx = rdx % 10 (r12 = 10)

    push rdx                                        ; rdx to stack, rdx - digit of number

    inc  r13                                        ; r13++, r13 = counter of dex digits

    cmp  eax, 0                                     ; if (edx != 0) {

    jne  NewDigitDex                                ;   goto NewDigitDex }

;---Output-dex-number-from stack-to-buffer-----------------------------------------------

    mov  rdx, r14                                   ; rdx = r14, back old value of rdx
    xor  eax, eax                                   ; rax = 0

NewDigitsInDexOutput:

    pop  rax                                        ; take rax from stack
                                                    ; rax = some digit of dex number
    add  eax, 30h                                   ; rax += 30h to find ASCII code of number

    cmp  rdx, BufferLen                             ; if (rdx >= BufferLen) {
    jnb  BufferOverflow                             ;   goto BufferOverflow }

    mov  [Buffer + rdx], al                         ; Buffer[rdx] = al
    inc  rdx                                        ; rdx++

BufferOverflow:

    dec  r13                                        ; if (!--r13) {
    jne  NewDigitsInDexOutput                       ;   goto NewDigitsInDexOutput }

;---Write-Buffer-------------------------------------------------------------------------

    mov  rsi, Buffer                                ; rsi = Buffer

    mov  rax, 0x01                                  ; write64 (rdi, rsi, rdx)
    mov  rdi, 1                                     ; stdout

    syscall

    pop  r15                                        ;------------------------------------
    pop  r14                                        ;                                   |
    pop  r13                                        ;    Take saved values of Callee    |
    pop  r12                                        ;    saved registers from stack     |
    pop  rbp                                        ;                                   |
    pop  rbx                                        ;------------------------------------

    ret

;---data---------------------------------------------------------------------------------

section     .data

Buffer:     TIMES 256 db 0
BufferLen:  equ 256

section     .note.GNU-stack

%endif
