#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {

	uint32_t s = 0x7fffffff; // 0111111111111111111
	// uint32_t z = 0x0; // 000000000

	uint32_t a = 0x80000000;  // 100000000000000
	//uint32_t h = 0xffffffff;


	if ((f & a) == a) {
		f = (f & s);
		return f;
	} 
	if ((f & a) == 0x0) {
		f = (f | a);
	}


    return f; // REPLACE ME WITH YOUR CODE
}
