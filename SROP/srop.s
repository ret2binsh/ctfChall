	global	_start
_start:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rax, [rbp-32]
	mov	edx, 200
	mov	rsi, rax
	mov	edi, 0
	xor	rax, rax
	syscall
	call     _start+0x23
	mov	rax, 0x3c
	syscall
	pop	rax
	ret
