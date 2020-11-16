# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                  # int main(void) {

    la $a0, prompt     # printf("Enter how many: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall
    move $s0, $v0       # $s0 = how_many

    li $s1, 1           # $s1 = n

n:
    bgt $s1, $s0, end   # n > howmany goto end

    li $s2, 0           # $s2 = total = 0
    li $s3, 1           # $s3 = j = 1

nn:
    bgt $s3, $s1, jjj   # j > n goto jjj

    li $s4, 1           # $s4 = i = 1

ii:
    bgt $s4, $s3, i     # i > j goto i
    add $s2, $s2, $s4     # total++
    add $s4, $s4, 1     # i++

    b ii

i:
    add $s3, $s3, 1     # j++

    b nn

jjj:
    move $a0, $s2          #   printf("%d", total);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $s1, $s1, 1     # n++

    b n

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter how many: "
