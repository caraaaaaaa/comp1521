# this code reads 1 integer and prints it
# add code so that prints 1 iff
# the least significant (bottom) byte of the number read
# is equal to the 2nd least significant byte
# and it prints 0 otherwise

main:
    li   $v0, 5   
    syscall
    move $t1, $v0    # number in $t1
    li $t2, 255
    li $t3, 65280
    and $t2, $t1, $t2
    and $t3, $t1, $t3
    sra $t3, $t3, 8
    # PUT YOUR CODE HERE
    beq $t2, $t3, one
    li $a0, 0
    b print
one:
    li $a0, 1    
print:    
    li   $v0, 1    # print %d
    syscall

    li   $a0, '\n'
    li   $v0, 11
    syscall

    li   $v0, 0
    jr   $ra
