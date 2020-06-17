global _start
_start:
	mov al, 255		
	sub al, 244 
	mov eax, 1		; sys_exit system call
	int 0x80		; interrupt for system call