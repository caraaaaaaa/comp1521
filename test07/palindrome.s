# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #


    li $a1, 0        # $a1 i
    li $t0, 0
loop:    
    la $a2, line
    add $a2, $a2, $a1
    lb $a3, ($a2)
    beq $a3, $t0, loop2
    add $a1, $a1, 1
    b loop

loop2:
    sub $t1, $a1, 2   # $t1, k
    li $a1, 0       # $a1, j
loop3:    
    bgt $a1, $t1, print_p

    la $t2, line
    add $t3, $t2, $t1    #k
    add $t4, $t2, $a1    #j
    lb $t5, ($t3)       # [k]
    lb $t6, ($t4)       # [j]
    bne $t5, $t6, print_not
    add $a1, $a1, 1   # j++
    sub $t1, $t1, 1   # k--
    b loop3

print_not:
    la   $a0, not_palindrome    # print not
    li   $v0, 4
    syscall
    b return

print_p:
    la   $a0, palindrome       # print palin
    li   $v0, 4
    syscall

return:
    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

