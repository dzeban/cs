section .text
global _start
_start:
	mov eax, 123
	call _abs
	mov eax, -9125
	call _abs

	mov ebx, 0
	mov eax, 1
	int 0x80
	ret

; Argument is in eax, output is in eax too
global _abs
_abs:
	cmp eax, 0
	jge .ret
	neg eax
.ret:
	ret

; vim: ft=nasm
