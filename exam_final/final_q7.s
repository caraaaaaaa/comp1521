# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print theintgers read in reverse order

main:
    li $t1, 0      # t1 sum
    li $t2, 0      #t2 i
compare:
    bge $t1, 42, print    
    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t0, $v0      # t0 x

    mul $t3, $t2, 4   
    la $t4, numbers
    add $t4, $t4, $t3
    sw $t0, ($t4)

    addi $t2, $t2, 1  # i++
    add $t1, $t1, $t0
    b compare

print:
    addi $t2, $t2, -1
    bltz $t2, return

    mul $t3, $t2, 4
    la $t4, numbers
    add $t4, $t4, $t3
    lw $a0, ($t4)

    # move $a0, $v0      #   printf("%d\n", x);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    
    b print

return:
    li   $v0, 0        # return 0
    jr   $ra

.data

numbers: .space 40000