# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall

    ble $v0, 49, pfl
    ble $v0, 64, pps
    ble $v0, 74, pcr
    ble $v0, 84, pdn
    bge $v0, 85, phd

           # return

pfl:
    la $a0, fl

    li $v0, 4
    syscall

    b end

pps:
    la $a0, ps

    li $v0, 4
    syscall

    b end

pcr:
    la $a0, cr

    li $v0, 4
    syscall

    b end

pdn:
    la $a0, dn

    li $v0, 4
    syscall

    b end

phd:
    la $a0, hd

    li $v0, 4
    syscall

    b end


end:
    jr $ra 


    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
