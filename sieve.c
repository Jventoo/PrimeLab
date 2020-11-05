#include "sieve.h"
#include <math.h>

void sieve(BitVector *v) {
  bv_set_all_bits(v);
  bv_clr_bit(v, 0);
  bv_clr_bit(v, 1);
  uint32_t len = bv_get_len(v);
  for (uint32_t i = 2; i < sqrtl(len); i++) {
    if (bv_get_bit(v, i)) {
      for (uint32_t k = 0; (k + i) * i <= len; k++) {
        bv_clr_bit(v, (k + i) * i);
      }
    }
  }
  return;
}
