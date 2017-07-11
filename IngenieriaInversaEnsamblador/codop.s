# codop.s

.text
_start: .globl _start

	xor %eax, %eax
	nop

	xor $1, %eax
	xor $0, %ebx
	int $0x80
	nop

	jmp .
	nop

	xor %eax, %eax
	nop
 	call empezar
empezar:
	nop
