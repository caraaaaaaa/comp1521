main:                           # int main(void)
    la  $a0, prompt             # printf("Enter a number: ");
    li  $v0, 4
    syscall

    li  $v0, 5                  # scanf("%d", number);
    syscall
    move $s1, $v0


    li $s0, 1 

loop:
    bge $s0, $s1, end

    rem $s2, $s0, 7
    beq $s2, 0, seven
    rem $s2, $s0, 11
    beq $s2, 0, eleven

    add $s0, $s0, 1

    b loop


seven:
    move $a0, $s0                 # printf("%d", 42);
    li $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $s0, $s0, 1

    b loop

eleven:

    move $a0, $s0                 # printf("%d", 42);
    li $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $s0, $s0, 1

    b loop

end:
    #li $v0, 0
    jr  $ra                     # return

    .data
prompt: .asciiz "Enter a number: "