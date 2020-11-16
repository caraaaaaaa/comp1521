// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
	int ident = 0b001000 << 26;
	int ss = s << 21;
	int tt = t << 16;

	int result = 0;
	if ((i & 0b1000000000000000) == 0b0) {
		result = ident + ss + tt + i;
	} else {
		i = 65536 + i;
		// printf("%d\n", i);
		result = ident + ss + tt + i;
	}
	

    return result; // REPLACE WITH YOUR CODE

}
