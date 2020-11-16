#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {

	uint32_t exp = f >> 23;

	uint32_t s = 0x100;

	if ((exp & s) == s) {
		exp = (exp & 0xff);
	}

    return exp; // REPLACE ME WITH YOUR CODE
}
