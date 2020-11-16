# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print their sum

li $t1, 0   # sum t1
main:
    
    bge $t1, 42, print
    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t0, $v0    # x in t0
    add $t1, $t1, $t0
    b main

print:
    move $a0, $t1      #   printf("%d\n", x);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        # return 0
    jr   $ra
