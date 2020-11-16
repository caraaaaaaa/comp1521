main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $t1, 0       # $t1 = i = 0

loopi:
    bge $t1, $t0, end

    li $t2, 0           # $t2 = j = 0

loopii:
    bge $t2, $t0, loopj

    la $a0, prompt          #   printf("%c", *);
    li $v0, 4
    syscall

    addi $t2, $t2, 1
    b loopii

loopj:
    addi $t1, $t1, 1

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    b loopi    

end:
    li $v0, 0           # return 0
    jr $31

.data
    prompt: .asciiz "*"