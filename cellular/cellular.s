########################################################################
# COMP1521 20T2 --- assignment 1: a cellular automaton renderer
#
# Written by Zixuan Guo (z5173593), July 2020.
# 


# Maximum and minimum values for the 3 parameters.

MIN_WORLD_SIZE    =    1
MAX_WORLD_SIZE    =  128
MIN_GENERATIONS    = -256
MAX_GENERATIONS    =  256
MIN_RULE    =    0
MAX_RULE    =  255

# Characters used to print alive/dead cells.

ALIVE_CHAR    = '#'
DEAD_CHAR    = '.'

# Maximum number of bytes needs to store all generations of cells.

MAX_CELLS_BYTES    = (MAX_GENERATIONS + 1) * MAX_WORLD_SIZE

    .data

# `cells' is used to store successive generations.  Each byte will be 1
# if the cell is alive in that generation, and 0 otherwise.

cells:    .space MAX_CELLS_BYTES


# Some strings you'll need to use:

prompt_world_size:    .asciiz "Enter world size: "
error_world_size:    .asciiz "Invalid world size\n"
prompt_rule:        .asciiz "Enter rule: "
error_rule:        .asciiz "Invalid rule\n"
prompt_n_generations:    .asciiz "Enter how many generations: "
error_n_generations:    .asciiz "Invalid number of generations\n"



    .text

    #
    # $s0: int world_size 
    # $s1: int rule
    # $s2: int n_generations
    # $s3: int reverse
    # $s4: first address of cells
    # $s5: int left 
    # $s6: int centre
    # $s7: int right

    # temp registers -- 
    # $t0: 
    # $t1: 
    # $t2: 
    # $t3: 

    

main:
# read 3 integer parameters from stdin    

            ##################################    
            ########## world size ############
            ##################################  
    la $a0, prompt_world_size             #printf("Enter world size: ");
    li $v0, 4
    syscall

    li  $v0, 5                            # scanf("%d", &world_size);
    syscall
    move $s0, $v0

# if (world_size < MIN_WORLD_SIZE || world_size > MAX_WORLD_SIZE)
    blt $s0, MIN_WORLD_SIZE, print_invalid_word_size
    bgt $s0, MAX_WORLD_SIZE, print_invalid_word_size
    b read_rule

print_invalid_word_size:
    la $a0, error_world_size              # printf("Invalid world size\n");
    li $v0, 4
    syscall
    b exit_error                          # return 1;


            ##################################    
            ########## read rule  ############
            ##################################  
read_rule:            
    la $a0, prompt_rule                   #printf("Enter rule: ");
    li $v0, 4
    syscall

    li  $v0, 5                            # scanf("%d", &rule);
    syscall
    move $s1, $v0

#if (rule < MIN_RULE || rule > MAX_RULE) goto print "Invalid rule\n"
    blt $s1, MIN_RULE, print_invalid_rule
    bgt $s1, MAX_RULE, print_invalid_rule
    b read_generations

print_invalid_rule:
    la $a0, error_rule                    # printf("Invalid rule\n");
    li $v0, 4
    syscall
    b exit_error                          #return 1;


            ##################################    
            ######## read generations ########
            ##################################  
read_generations:            
    la $a0, prompt_n_generations          #printf("Enter how many generations: ");
    li $v0, 4
    syscall

    li  $v0, 5                            # scanf("%d", &n_generations);
    syscall
    move $s2, $v0

#if (n_generations < MIN_GENERATIONS || n_generations > MAX_GENERATIONS) 
    blt $s2, MIN_GENERATIONS, print_invalid_generations
    bgt $s2, MAX_GENERATIONS, print_invalid_generations
    b print_new_line

print_invalid_generations:
    la $a0, error_n_generations           # printf("Invalid number of generations\n");
    li $v0, 4
    syscall
    b exit_error                          #return 1;


            ##################################    
            ######## print new line ##########
            ################################## 
print_new_line:
    li $a0, '\n'                          # putchar('\n');
    li $v0, 11
    syscall


la $s4, cells                             # load start address of cells


            ##################################    
            ######## define reverse ##########
            ################################## 
#negative generations means show the generations in reverse
reverse_negative_generations:    
    li $s3, 0                            # int reverse = 0;
    bgez $s2, store_stack_initial        # if (n_generations < 0) goto store stack
    li $s3, 1                            # reverse = 1;

    sub $s2, $0, $s2                     # n_generations = -n_generations;


            ##################################    
            ######## store in stack ##########
            ################################## 
store_stack_initial:
    addi $sp, $sp, -32
    sw   $s7, 28($sp)                    # store right in $s7 to stack
    sw   $s6, 24($sp)                    # store centre in $s6 to stack
    sw   $s5, 20($sp)                    # store left in $s5 to stack
    sw   $s4, 16($sp)                    # store start address in $s4 to stack
    sw   $s3, 12($sp)                    # store reverse in $s3 to stack
    sw   $s2, 8($sp)                     # store generation in $s2 to stack
    sw   $s1, 4($sp)                     # store rule number in $s1 to stack
    sw   $s0, 0($sp)                     # store world_size in $s0 to stack



            ##################################    
            #### define fisrt generation #####
            ################################## 
 # the first generation always has a only single cell which is alive
 # this cell is in the middle of the world
        
    div $s0, $s0, 2                      # $s0: bits of [0][world_size/2] -- world size * 2
    add $s0, $s0, $s4                    # $s0: address of [0][world_size/2]
    li $t3, 1
    sb $t3, ($s0)                        # cells[0][world_size / 2] = 1;

    lw $s0, 0($sp)                       # load back the original value of world_size in $s0


            ##################################    
            ###### call run_generation #######
            ################################## 
li $t0, 1                                # int g = 1;
call_run_generation:
    ble $t0, $s2, run_generation         # g <= n_generations goto run_generation


            ##################################    
            #### call print_generation #######
            ################################## 
beq $s3, 1, negative_print_generation    # if (reverse) goto negative_print_generation
                    
positive_print_generation:
    li $t0, 0                            # int g = 0
positive_print_generation_loop:
    ble $t0, $s2, print_generation       # g <= n_generations goto print_generation
    bgt $t0, $s2, exit_syscall
positive_print_generation_loop_back:
    add $t0, $t0, 1                      # g++
    b positive_print_generation_loop


negative_print_generation:
    move $t0, $s2                        # int g = n_generations
negative_print_generation_loop:
    bgez $t0, print_generation           # g >= 0 goto print_generation
    bltz $t0, exit_syscall
negative_print_generation_loop_back:    
    sub $t0, $t0, 1                      # g--
    b negative_print_generation_loop


            ##################################    
            ############ exit main ###########
            ################################## 
exit_syscall:    
    lw   $s0, 0($sp)                     # load world_size in $s0 from stack
    lw   $s1, 4($sp)                     # load rule number in $s1 from stack
    lw   $s2, 8($sp)                     # load generation in $s2 from stack
    lw   $s3, 12($sp)                    # load reverse in $s3 from stack
    lw   $s4, 16($sp)                    # load start address in $s4 from stack                    
    lw   $s5, 20($sp)                    # load left in $s5 from stack
    lw   $s6, 24($sp)                    # load centre in $s6 from stack
    lw   $s7, 28($sp)                    # load right in $s7 from stack
    addi $sp, $sp, 32

    li    $v0, 0
    jr    $ra

exit_error:
     li    $v0, 10
     syscall




    #
    # Given `world_size', `which_generation', and `rule',
    # calculate a new generation according to `rule' and store it in `cells'.
    #
            ##################################    
            ######### RUN_GENERATION #########
            ##################################
run_generation:
    li $t1, 0                                     # int x = 0
    run_generation_loop:
        bge $t1, $s0, run_generation_loop_addg    # x >= world_size go back to main
        li $s5, 0                                 # int left = 0
        blez $t1, run_generation_centre           # x <= 0, goto run_generation_centre
        
    run_generation_left:                        
        sub $t2, $t1, 1                           # $t2 = x - 1
        sub $t3, $t0, 1                           # $t3 = g - 1
        
        mul $t3, $t3, $s0                         # $t3 = (g-1) * world_size
        add $t2, $t2, $t3                         # $t2 =  (g-1) * world_size + (x-1)
        add $t2, $t2, $s4                         # $t2 = $s4 + bits

        lb $s5, ($t2)                             # left = cells[which_generation - 1][x-1]

    run_generation_centre:
        sub $t3, $t0, 1                           # $t3 = g - 1
        mul $t3, $t3, $s0                         # $t3 = (g-1) * world_size
        add $t2, $t1, $t3                         # $t2 = x + (g-1) * world_size
        add $t2, $s4, $t2                         # $t2 = address of [][]

        lb $s6, ($t2)                             # centre = cells[which_generation - 1][x]

    li $s7, 0                                     # $s7 = right = 0

    sub $t2, $s0, 1                               # $t2 = world_size - 1
    bge $t1, $t2, run_generation_state            # x >= world_size - 1 goto calculate state
    sub $t2, $t0, 1                               # $t2 = g - 1
    mul $t2, $t2, $s0                             # $t2 = (g-1) * world_size
    add $t2, $t2, 1                               # $t2 = (g-1) * world_size + 1
    add $t2, $t2, $t1                             # $t2 = (g-1) * world_size + 1 + x

    add $t2, $s4, $t2                             # $t2 = address of cells[which_generation-1][x+1]
    lb $s7, ($t2)                                 # right = cells[which_generation - 1][x+1]


    # calculate state: state = left << 2 | centre << 1 | right << 0
    run_generation_state:
        sll $s5, $s5, 2                           # $s5 = left << 2
        sll $s6, $s6, 1                           # $s6 = centre << 1
        sll $s7, $s7, 0                           # $s7 = right << 0

        or $t3, $s5, $s6                          # state = left << 2 | centre << 1
        or $t3, $t3, $s7                          # state = left << 2 | centre << 1 | right << 0

        li $a0, 1
        sll $t3, $a0, $t3                         # bit = 1 << state

    # calculate set
    run_generation_set:
        and $t3, $t3, $s1                         # set = rule & bit

    # get address of cells[which_generation][x]
        mul $t2, $t0, $s0                         # $t2: g * world_size
        add $t2, $t2, $t1                         # $t2: g * world_size + x
        add $t2, $t2, $s4                         # $t2: address of [which)generation][x]

    # if (set)
    bne $t3, 0, run_generation_one                # set != 1, goto zero
    li $t3, 0
    sb $t3, ($t2)                                 # cells[which_generation][x] = 0

    addi $t1, $t1, 1                              # x++
    b run_generation_loop
        
    run_generation_one:
        li $t3, 1
        sb $t3, ($t2)                             # cells[which_generation][x] = 1

        addi $t1, $t1, 1                          # x++
        b run_generation_loop

    run_generation_loop_addg:    
        add $t0, $t0, 1                           # g++
        b call_run_generation
        
    jr  $ra                                       # return from function run_generation

    


    #
    # Given `world_size', and `which_generation', print out the
    # specified generation.
    #
            ##################################    
            ######## PRINT_GENERATION ########
            ##################################

print_generation:
    move $a0, $t0 
    li $v0, 1                                     # printf("%d", which_generation)
    syscall

    li $a0, '\t'                                  # printf("\t");
    li $v0, 11
    syscall

    print_generation_loop:
        li $t1, 0                                 # $t1: x = 0
    print_generation_loop_back:
        bge $t1, $s0, print_generation_newline    # x >= world_size goto print newline

        mul $t2, $t0, $s0                         # t2 = g * world_size
        add $t2, $t2, $t1                         # t2 = g * world_size + x
        add $t2, $t2, $s4                         # t2 = address[g][x]
        lb $t3, ($t2)

        beq $t3, 1, print_generation_alive        # cells[g][x] = 1 goto print_alive
        li $a0, DEAD_CHAR                         # else, printf(".");
        li $v0, 11
        syscall

        b print_generation_addx

    print_generation_alive:
        li $a0, ALIVE_CHAR                        # printf("#");
        li $v0, 11
        syscall

    print_generation_addx:
        add $t1, $t1, 1                           # x++
        b print_generation_loop_back    

    print_generation_newline:
        li $a0, '\n'                              # printf("\n");
        li $v0, 11
        syscall

    beq $s3, 1, negative_print_generation_loop_back      # if reverse = 1, goto negative print generation
    b positive_print_generation_loop_back                # else, goto positive print generation

    jr  $ra                                              # return from function print_generation
