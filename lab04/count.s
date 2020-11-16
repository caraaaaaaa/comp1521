# read a number n and print the integers 1..n one per line

main:                           # int main(void)
    la  $a0, prompt             # printf("Enter a number: ");
    li  $v0, 4
    syscall

    li  $v0, 5                  # scanf("%d", number);
    syscall
    move $s1, $v0

    li $s0, 1  # a1 counter
      # a2 number constant


loop:
    bgt $s0, $s1, end

    move $a0, $s0                 # printf("%d", 42);
    li $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $s0, $s0, 1
    #sub $s1, $s1 1

    b loop

end:
    #li $v0, 0
    jr  $ra                     # return

    .data
prompt: .asciiz "Enter a number: "
