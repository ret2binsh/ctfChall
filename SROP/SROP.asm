BITS 64

		org 0x401000

ehdr:							; ELF64_Ehdr
		db	0x7f, "ELF", 2, 1, 1, 0		;e_ident = 0x7ELF, 64-bit, little endian, Current Version
	times 8	db	0				;mandatory padding
		dw	2				;e_type = executable file
		dw	62				;e_machine = amd64
		dd	1				;e_version = current
		dq	_start				;e_entry
		dq	phdr - $$			;e_phoff
		dq	0				;e_shoff
		dd	0				;e_flags
		dw	ehdrsize			;e_ehsize
		dw	phdrsize			;e_phentsize
		dw	1				;e_phnum
		dw	0				;e_shentsize
		dw	0				;e_shnum
		dw	0				;e_shstrndx

ehdrsize	equ	$ - ehdr			;calculate ehdrsize

phdr:							; ELF64_Phdr
		dd	1				;p_type = Loadable program segment
		dd	5				;p_flags = b101 = Read and Execute
		dq	0				;p_offset
		dq	$$				;p_vaddr
		dq	$$				;p_paddr
		dq	filesize			;p_filesz = overall filesize
		dq	filesize			;p_memsz
		dq	0x1000				;p_align

phdrsize	equ	$ - phdr			;calculate phdrsize

	section .data
flag:	db	"/bin/sh", 0

	global	_start

	section	.text
_read:
	push	rbp
	mov	rbp, rsp
	mov	edx, 0x200
	lea	rsi, [rbp-32]
	mov	edi, 0
	xor	rax, rax
	syscall
	pop	rbp
	ret

_start:
	push	rbp
	mov	rbp, rsp
	call	_read
	mov	rax, 0x3c
	syscall
	pop	rax
	ret

filesize	equ	$ - $$				;calculate entire filesize
