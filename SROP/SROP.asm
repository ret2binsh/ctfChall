	section .data
binsh:	db	"/bin/sh", 0

	global	_start

	section	.text
_read:
	push	rbp
	mov	rbp, rsp
	lea	rax, [rbp-32]
	mov	edx, 200
	mov	rsi, rax
	mov	edi, 0
	xor	rax, rax
	syscall
	xor	rax, rax
	pop	rbp
	ret

_start:
	push	rbp
	mov	rbp, rsp
	mov	eax, 0x0
	call	_read
	xor	rax, rax
	mov	rax, 0x3c
	syscall
	pop	rax
	ret
