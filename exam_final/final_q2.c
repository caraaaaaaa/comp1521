#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
//#include <stdio.h>

// given a uint32_t value,
// return 1 iff the least significant (bottom) byte
// is equal to the 2nd least significant byte; and
// return 0 otherwise
int final_q2(uint32_t value) {
    // PUT YOUR CODE HERE
    uint32_t last = value & 0b11111111;
    uint32_t second = (value & 0b1111111100000000) >> 8; 

    //printf("%d %d\n", last, second);
    int result = 0;
    if (last == second) {
        result = 1;
    }
    return result;
}
