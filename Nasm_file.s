;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
section .text

start:

	call my_input; utyutyu
;number operator 2 
; -------start-while-4-----------------------

; test-4

	mov r8, [0]; utyutyu

	mov r8, 20
	jb end_while4:
; action-4

	mov r8, [0]; utyutyu


	call my_print
;number operator 6 
	mov r8, 8

	call my_print
;number operator 8 
	mov r8, [0]; utyutyu

	mov r9, 1
	add r8, r9;number operator 11 
	pop [0]; utyutyu
;number operator 11 ;number operator 12 ;number operator 12 ;number operator 12 ;number operator 12 
end_while4:
; -------end-while-4------------------------
;number operator 12 ;number operator 13 ;number operator 13 ;number operator 13 
	call my_hlt

section .note.GNU-stack
