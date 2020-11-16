# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:

    # PUT YOUR CODE
    li $t0, 0           # int i = 0
    la $t1, prime   

loop1:    
    bge $t0, 1000, loop2    #while (i < 1000) 
    mul $t2, $t0, 4
    add $t2, $t2, $t1
    li $t4, 1
    sw $t4, ($t2)        #prime[i] = 1;
    add $t0, $t0, 1      # i++
    j loop1

loop2:
	li $t0, 2            # i = 2
loop3:
	bge $t0, 1000, return   # while (i < 1000)
	mul $t2, $t0, 4
	add $t2, $t1, $t2
	lw $t2, ($t2)
	bne $t2, 1, loop4       # if (prime[i]) {

	move $a0, $t0         # printf("%d\n", i);
	li $v0, 1
	syscall

	li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

	mul $t3, $t0, 2     # int j = 2 * i;
	loop5:
		bge $t3, 1000, loop4   # while (j < 1000) {
		mul $t2, $t3, 4
		add $t2, $t2, $t1
		li $t4, 0
		sw $t4, ($t2)         # prime[j] = 0;
		add $t3, $t3, $t0    # j = j + i;
		j loop5

loop4:
	add $t0, $t0, 1      # i++
	j loop3	

return:
    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000