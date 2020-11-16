// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    // PUT YOUR CODE HERE
    uint64_t result = 0;
    uint64_t sw = 0x2;
    uint64_t ap = 0x1;

    for (int i = 0; i < 32; i++) {
        uint64_t l = sw & value;
        uint64_t r = ap & value;

        l = l >> 1;
        r = r << 1;
        
        result = result + l + r;

        sw = sw << 2;
        ap = ap << 2;
    }

    return result;
}
