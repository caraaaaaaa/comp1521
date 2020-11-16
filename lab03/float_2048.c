// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    // PUT YOUR CODE HERE
    float_components_t ans;

    ans.sign = (f & 0x80000000) >> 31;
    ans.exponent = (f & 0x7f800000) >> 23;
    ans.fraction = f & 0x7fffff;
    
    if (ans.exponent == 0xff && ans.fraction == 0x400000) {
        return f;
    } else if (ans.sign == 0x00 && ans.exponent == 0xff && !(ans.fraction == 0x400000)) {
       return f;
    } else if (ans.sign == 0x01 && ans.exponent == 0xff) {
       return f;
    } else if (ans.exponent == 0x00 && ans.fraction == 0x00000) {
        return f;
    } else {
    	ans.exponent = ans.exponent + 0xb;
    	f = (ans.sign << 31) + (ans.exponent << 23) + (ans.fraction);
    	if (ans.exponent >= 0xff) {
    		f = 2139095040;
    		//f = 0x5;
    		//printf("aaa\n");
    	} else if (f < -2147483647 && f < 0) {
    		f = -2139095040;
    	}
    	
    }
    
    return f;
}
