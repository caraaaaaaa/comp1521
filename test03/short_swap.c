// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    // PUT YOUR CODE HERE
    uint16_t high = 0xff00;
    uint16_t low = 0x00ff;
    uint16_t hb = high & value;
    uint16_t lb = low & value;
    hb = hb >> 8;
    lb = lb << 8;
    uint16_t result = hb + lb;
    return result;
}
