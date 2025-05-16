;--------------------------------------------------------------------------------------------------
;                           Programming language
;                         (c) 2025 Muratov Artyom
;--------------------------------------------------------------------------------------------------
global  _start

section .text

%INCLUDE "stdlib.s"

_start:

	and rsp, -16
;number operator 2 ;number operator 4 ;number operator 5 ;number operator 5 ;number operator 5 
	call _my_hlt

section .note.GNU-stack
