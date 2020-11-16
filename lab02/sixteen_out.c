//
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);
int get_nth_bit(short value, int n);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc

char *sixteen_out(int16_t value) {

    // PUT YOUR CODE HERE
    // value = 0;
    // long mask = 1111111111111111;
    char *result = malloc(sizeof(char) * 17);
    for (int n = 0; n < 16; n++) {
        
        int bit = get_nth_bit(value, n);
        result[15 - n] = '0' + bit;

    }
    result[16] = '\0';
    return result;

}

int get_nth_bit(short value, int n) {
    return (value >> n) & 1;
}
