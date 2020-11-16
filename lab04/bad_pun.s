main:
	la $a0, prompt
	li $v0, 4
	syscall

	jr $ra

.data
	prompt: .asciiz "I MIPS you!\n"


		