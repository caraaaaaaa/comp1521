#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);
// int get_nth_bit(short value, int n);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    int lb_mask = 0b0000000011111111;
	int hb_mask = 0b1111111100000000;
	int re = 0;

	lb_mask = lb_mask & bcd_value;
	hb_mask = hb_mask & bcd_value;

	hb_mask = hb_mask >> 8;
	
	if(lb_mask >= 99){
		re = 99;
		return re;
	}

	re = hb_mask * 10 + lb_mask;
	if(re >= 99){
		re = 99;
		return re;
	}
    return re;
}