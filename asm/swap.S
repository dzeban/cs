section .text
global _start
_start:
	mov eax, val1
	mov ebx, val2
	call swap

	mov eax, [val1]
	mov ebx, [val2]

	mov eax, 1
	mov ebx, 0
	int 0x80
	ret

global swap
swap:
	mov esi, [eax]
	mov edi, [ebx]
	mov [eax], edi
	mov [ebx], esi
	ret

section .data
val1: db 0x01, 0x02, 0x03, 0x04
val2: db 0x09, 0x08, 0x07, 0x06
; vim: ft=nasm
