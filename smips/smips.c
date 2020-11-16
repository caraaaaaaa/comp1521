// 1521 ASST 2 smips.c
// Zixuan Guo (z5173593)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ZERO 0
#define REGISTERS 32
#define SYSCALL 2
#define ADD 3
#define SUB 4
#define AND 5
#define OR 6
#define SLT 7
#define MUL 8
#define BEQ 9
#define BNE 10
#define ADDI 11
#define SLTI 12
#define ANDI 13
#define ORI 14
#define LUI 15
#define WRONG 16
#define UNKNOWN 404

#define SYS_PRINT_INT 1
#define SYS_EXIT 10
#define SYS_PRINT_CHAR 11

#define SHIFT_D 11
#define SHIFT_T 16
#define SHIFT_I 16
#define SHIFT_S 21
#define SHIFT_INSTRUCT 26

#define S_MASK 0b11111000000000000000000000
#define T_MASK 0b111110000000000000000
#define D_MASK 0b1111100000000000
#define I_MASK 0b1111111111111111
#define NEG_I_MASK 0b1000000000000000
#define TRANS_NEG 65536
#define LAST_MASK 0b11111111111

#define OR_MASK 0b100101
#define ADD_MASK 0b100000
#define SUB_MASK 0b100010
#define AND_MASK 0b100100
#define SLT_MASK 0b101010
#define BEQ_MASK 0b100
#define BNE_MASK 0b101
#define ORI_MASK 0b1101
#define ADDI_MASK 0b1000
#define SLTI_MASK 0b1010
#define ANDI_MASK 0b1100
#define SYSCALL_MASK 0b1100
#define MUL_LAST_MASK 0b10
#define LUI_INDENT_MASK 0b1111
#define MUL_INDENT_MASK 0b11100




void add(int *registers, int d, int s, int t);
void sub(int *registers, int d, int s, int t);
void and(int *registers, int d, int s, int t);
void or(int *registers, int d, int s, int t);
void slt(int *registers, int d, int s, int t);
void mul(int *registers, int d, int s, int t);

int beq(int *registers, int s, int t, int I, int instruct_num);
int bne(int *registers, int s, int t, int I, int instruct_num);
void addi(int *registers, int t, int s, int I);
void slti(int *registers, int t, int s, int I);
void andi(int *registers, int t, int s, int I);
void ori(int *registers, int t, int s, int I);
void lui(int *registers, int t, int I);

int syscall(int *registers);

int hex_to_instruction (uint32_t instruction);
void print_program(int mode, uint32_t instruction);
int run_program (int *registers, int mode, uint32_t instruction, int instruct_num);



int main(int argc, char *argv[]) {
	// check for argument error
	if (argc != 2) {
		printf("Please enter 2 arguments only.\n");
		return 0;
	}

	// read file from argument
	FILE *fp = fopen(argv[1], "r");
	uint32_t c;

	if (fp == NULL) {
		perror("Error in opening file");
		return(-1);
	}

	int registers[REGISTERS] = {0};
	uint32_t programs[1000] = {0};


	///////////////////////////////////////////////
	//////////////  PROGRAM  //////////////////////
	///////////////////////////////////////////////
	

	// read file line by line
	int instruct_num = 0;
	int j = 0;
	while ( !feof(fp) ) {
		// get char from file and transfer to numbers
		c = fgetc(fp) - 48;

		// transfer a~f to 10-16
		if (c >= 49 && c <= 54) {
			c = c - 39;
		}

		// use '\n' to distinguish the end of instructions
		if ((c + 48) == '\n') {
			// when only '\n' in a line
			if (j == 0) {
				programs[instruct_num] = programs[instruct_num] >> (4 * (8 - j) - 1);
			// if hex instruction is not 8 bits
			} else if (j < 8) {
				programs[instruct_num] = programs[instruct_num] >> (4 * (8 - j));
			}
			instruct_num++;
			j = 0;
		} else {
			// store instructions into programs[]
			programs[instruct_num] = programs[instruct_num] + (c << (4 * (7- j)));
			j++;
		}
	}
	
	fclose(fp);


	// check for invalid instruction code
	for (int i = 0; i < instruct_num; i++) {
		uint32_t instruction = programs[i];
		int modde = hex_to_instruction (instruction);

		if (modde == WRONG) {
			printf("%s:%d: invalid instruction code: %08X\n", argv[1], i + 1, instruction);
			exit(0);
		}
	}

	
	// print program
	printf ("Program\n");

	for (int i = 0; i < instruct_num; i++) {
		uint32_t instruction = programs[i];
		int modde = hex_to_instruction (instruction);

		// print instruction
		if (i < 10) {
			printf("  %d: ", i);
		} else {
			printf(" %d: ", i);
		}
		print_program(modde, instruction);
		
	}
			
	///////////////////////////////////////////////
	//////////////  OUTPUT  ///////////////////////
	///////////////////////////////////////////////
	printf("Output\n");
	int out = 0;
	int i = 0;

	while (i < instruct_num && i >= 0) {
		// transfer hex to bin
		uint32_t instruction = programs[i];
		int modde = hex_to_instruction (instruction);

		// run program
		out = run_program (registers, modde, instruction, i);
		if (out != 0 && out != UNKNOWN) {
			i = out;
		} else if (out == UNKNOWN) {
			break;
		} else {
			i++;
		}
	}



	///////////////////////////////////////////////
	//////////////  REGISTER  /////////////////////
	///////////////////////////////////////////////

	printf("Registers After Execution\n");

	// print registers 0~31 if not equals to zero
	for (int counter = 0; counter < REGISTERS; counter++) {
		if (registers[counter] != 0) {
			if (counter < 10) {
				printf("$%d  = %d\n", counter, registers[counter]);
			} else {
				printf("$%d = %d\n", counter, registers[counter]);
			}
			
		}
	}
	

	return 0;
}


// return mode of instruction
// mode -> SYSCALL MUL ADD SUB AND OR SLT BEQ BNE ADDI SLTI ANDI ORI LUI
int hex_to_instruction (uint32_t instruction) {
	int ident = instruction >> SHIFT_INSTRUCT;
	int s = (instruction & S_MASK) >> SHIFT_S;
	int last = instruction & LAST_MASK;

	int mode = WRONG;

	if (instruction == SYSCALL_MASK) {
		mode = SYSCALL;
	} else if ((ident == MUL_INDENT_MASK) && (last == MUL_LAST_MASK)) {
		mode = MUL;
	} else if (ident == ZERO) {
		if (last == ADD_MASK) {
			mode = ADD;
		} else if (last == SUB_MASK) {
			mode = SUB;
		} else if (last == AND_MASK) {
			mode = AND;
		} else if (last == OR_MASK) {
			mode = OR;
		} else if (last == SLT_MASK) {
			mode = SLT;
		} else {
			mode = WRONG;
		}
	} else if (ident == BEQ_MASK) {
		mode = BEQ;
	} else if (ident == BNE_MASK) {
		mode = BNE;
	} else if (ident == ADDI_MASK) {
		mode = ADDI;
	} else if (ident == SLTI_MASK) {
		mode = SLTI;
	} else if (ident == ANDI_MASK) {
		mode = ANDI;
	} else if (ident == ORI_MASK) {
		mode = ORI;
	} else if ((ident == LUI_INDENT_MASK) && (s == ZERO)) {
		mode = LUI;
	} else {
		mode = WRONG;
	}

	return mode;	
}


// run program and change values of registers
int run_program (int *registers, int mode, uint32_t instruction, int instruct_num) {
	int s = (instruction & S_MASK) >> SHIFT_S;
	int t = (instruction & T_MASK) >> SHIFT_T;
	int d = (instruction & D_MASK) >> SHIFT_D;

	int I = instruction & I_MASK;
	if ((I & NEG_I_MASK) != ZERO) {
		I = I - TRANS_NEG;
	}

	// $0 should always be 0
	registers[0] = ZERO;
	int re = ZERO;

	if (mode == ADD) {
		add(registers, d, s, t);
	} else if (mode == SUB) {
		sub(registers, d, s, t);
	} else if (mode == AND) {
		and(registers, d, s, t);
	} else if (mode == OR) {
		or(registers, d, s, t);
	} else if (mode == SLT) {
		slt(registers, d, s, t);
	} else if (mode == MUL) {
		mul(registers, d, s, t);
	} else if (mode == ADDI) {
		addi(registers, t, s, I);
	} else if (mode == SLTI) {
		slti(registers, t, s, I);
	} else if (mode == ANDI) {
		andi(registers, t, s, I);
	} else if (mode == ORI) {
		ori(registers, t, s, I);
	} else if (mode == LUI) {
		lui(registers, t, I);
	} else if (mode == BEQ) {
		re = beq(registers, s, t, I, instruct_num);
	} else if (mode == BNE) {
		re = bne(registers, s, t, I, instruct_num);
	} else if (mode == SYSCALL) {
		re = syscall(registers);
	} 

	return re;
}


// print instructions in 'mpis' type
void print_program(int mode, uint32_t instruction) {
	int s = (instruction & S_MASK) >> SHIFT_S;
	int t = (instruction & T_MASK) >> SHIFT_T;
	int d = (instruction & D_MASK) >> SHIFT_D;

	int I = instruction & I_MASK;
	if ((I & NEG_I_MASK) != ZERO) {
		I = I - TRANS_NEG;
	}


	if (mode == ADD) {
		printf("add  $%d, $%d, $%d\n", d, s, t);
	} else if (mode == SUB) {
		printf("sub  $%d, $%d, $%d\n", d, s, t);
	} else if (mode == AND) {
		printf("and  $%d, $%d, $%d\n", d, s, t);
	} else if (mode == OR) {
		printf("or   $%d, $%d, $%d\n", d, s, t);
	} else if (mode == SLT) {
		printf("slt  $%d, $%d, $%d\n", d, s, t);
	} else if (mode == MUL) {
		printf("mul  $%d, $%d, $%d\n", d, s, t);
	} else if (mode == ADDI) {
		printf("addi $%d, $%d, %d\n", t, s, I);
	} else if (mode == SLTI) {
		printf("slti $%d, $%d, %d\n", t, s, I);
	} else if (mode == ANDI) {
		printf("andi $%d, $%d, %d\n", t, s, I);
	} else if (mode == ORI) {
		printf("ori  $%d, $%d, %d\n", t, s, I);
	} else if (mode == LUI) {
		printf("lui  $%d, %d\n", t, I);
	} else if (mode == BEQ) {
		printf("beq  $%d, $%d, %d\n", s, t, I);
	} else if (mode == BNE) {
		printf("bne  $%d, $%d, %d\n", s, t, I);
	} else if (mode == SYSCALL) {
		printf("syscall\n");
	} else {
		printf("Wrong instruction.\n");
	}
}



// add d = s + t
void add(int *registers, int d, int s, int t) {
	registers[d] = registers[s] + registers[t];
}

// sub d = s - t
void sub(int *registers, int d, int s, int t) {
	registers[d] = registers[s] - registers[t];
}

// and d = s & t
void and(int *registers, int d, int s, int t) {
	registers[d] = registers[s] & registers[t];
}

// or d = s | t
void or(int *registers, int d, int s, int t) {
	registers[d] = registers[s] | registers[t];
}

// slt s < t d = 1 else d = 0
void slt(int *registers, int d, int s, int t) {
	if (registers[s] < registers[t]) {
		registers[d] = 1;
	} else {
		registers[d] = ZERO;
	}
}

// mul d = s * t
void mul(int *registers, int d, int s, int t) {
	registers[d] = registers[s] * registers[t];
}

// beq s == t, PC +- I
int beq(int *registers, int s, int t, int I, int instruct_num) {
	int re = 0;
	if (registers[t] == registers[s]) {
		re = instruct_num + I;
	} 
	return re;
}

// bne s != t, PC +- I
int bne(int *registers, int s, int t, int I, int instruct_num) {
	int re = 0;
	if (registers[t] != registers[s]) {
		re = instruct_num + I;
	} 
	return re;
}

// addi t = s + I
void addi(int *registers, int t, int s, int I) {
	registers[t] = registers[s] + I;
}	

// slti t = (s < I)
void slti(int *registers, int t, int s, int I) {
	if (registers[s] < I) {
		registers[t] = 1;
	} else {
		registers[t] = 0;
	}
}	

// andi t = s & I
void andi(int *registers, int t, int s, int I) {
	registers[t] = registers[s] & I;
}	

// ori t = s | I
void ori(int *registers, int t, int s, int I) {
	registers[t] = registers[s] | I;
}

// lui t = I << 16
void lui(int *registers, int t, int I) {
	registers[t] = I << SHIFT_I;
}	


// syscall
int syscall(int *registers) {
	// $v0 = 1, print %d in $a0
	if (registers[2] == SYS_PRINT_INT) {
		printf("%d", registers[4]);
	// $v0 = 10, exit(0)	
	} else if (registers[2] == SYS_EXIT) {
		return 20;
	// $v0 = 11, print char in $a0	
	} else if (registers[2] == SYS_PRINT_CHAR) {
		printf("%c", registers[4]);
	// unknown syscall	
	} else {
		printf("Unknown system call: %d\n", registers[2]);
		return UNKNOWN;
	}

	return 0;
}
