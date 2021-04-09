section .text
    global _ft_read

extern ___error

_ft_read :
	mov rax, 0x2000003
	syscall
	jc end
	ret

end : 
	push rax
	call ___error
	pop qword [rax]
	mov rax, -1
	ret
