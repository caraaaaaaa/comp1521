# read a line and print its length

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li $a1, 0
    li $t0, 0
loop:    
    la $a2, line
    add $a2, $a2, $a1
    lb $a3, ($a2)
    beq $a3, $t0, print
    add $a1, $a1, 1
    b loop

print:
    la   $a0, str1       # printf("Line length: ");
    li   $v0, 4
    syscall

    move   $a0, $a1         # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Line length: "


# line of input stored here
line:
    .space 256

