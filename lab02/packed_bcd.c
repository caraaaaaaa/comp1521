#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    uint32_t re = 0;

	//32 bits mask
	uint32_t mask = 0b00000000000000000000000000001111;

	int n = 1;
	int shift = 0;
	while(1) {
		uint32_t temp = mask & packed_bcd_value;
		temp = temp >> shift;
		re = temp * n + re;
		n = n * 10;
		
		if(re >= 99999999) {
			re = 99999999;
			return re;
		}

		mask = mask << 4;
		if(mask == 0) {
			break;
		}

		shift = shift + 4;
	}

    return re;

}
