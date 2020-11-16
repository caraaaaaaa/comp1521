#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
	if ((n_rotations &= 15) == 0)
      return bits;
return (bits << n_rotations) | (bits >> (16 - n_rotations));

}
