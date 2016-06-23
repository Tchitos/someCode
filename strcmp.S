[BITS 64]

global mystrcmp
section .text

mystrcmp:
	xor r9, r9
	xor r8, r8
	xor rcx, rcx
	call compare
	ret

compare:
	mov r8b, byte [rsi + rcx]
	cmp byte [rdi + rcx], r8b
	je incr
	jmp soust
	ret

incr:
	inc rcx
	cmp byte [rsi + rcx], 0
	je end
	cmp byte [rdi + rcx], 0
	je end
	jmp compare
	ret

soust:
	mov r9b, r8b
	xor r8, r8
	mov r8b, byte [rdi + rcx]
	sub r9b, r8b


end:
	mov r9, 0
	ret
