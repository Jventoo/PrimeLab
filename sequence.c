#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "spn:"
#define DEFAULT_SIZE 1000

void palindrome(uint32_t to_base, uint32_t prime);

int main(int argc, char **argv) {
  int c = 0, n = DEFAULT_SIZE + 1;
  bool run_inters = false, run_pal = false;

  if (argc == 1) {
    puts("Error: no arguments supplied!");
    return -1;
  }

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 's':
      run_inters = true;
      break;
    case 'p':
      run_pal = true;
      break;
    case 'n':
      n = atoi(optarg) + 1;
      break;
    }
  }

  if (!run_inters && !run_pal) {
    puts("Error: must supply an operation!");
    return -1;
  }

  BitVector *bv = bv_create(n);
  sieve(bv);

  if (run_inters) {
    uint32_t prev_fib = 1, prev_lucas = -1;
    uint32_t fib = 2, lucas = 2, mers = 3;

    for (uint32_t i = 2; i < bv_get_len(bv); i++) {
      if (bv_get_bit(bv, i)) {
        printf("%d: prime", i);

        while (mers < i) {
          mers += 1;
          mers = (mers * 2) - 1;
        }
        if (i == mers) {
          printf(", mersenne");
        }

        while (fib < i) {
          uint32_t temp = fib;
          fib += prev_fib;
          prev_fib = temp;
        }
        if (i == fib) {
          printf(", fibonacci");
        }

        while (lucas < i) {
          uint32_t temp = lucas;
          lucas += prev_lucas;
          prev_lucas = temp;
        }
        if (i == lucas) {
          printf(", lucas");
        }

        printf("\n");
      }
    }
  }

  if (run_pal) {
    // Base 2
    printf("Base  %d\n", 2);
    puts("---- --");
    for (uint32_t i = 0; i < bv_get_len(bv); i++) {
      if (bv_get_bit(bv, i)) {
        palindrome(2, i);
      }
    }
    printf("\n");

    // Base 9
    printf("Base  %d\n", 9);
    puts("---- --");
    for (uint32_t i = 0; i < bv_get_len(bv); i++) {
      if (bv_get_bit(bv, i)) {
        palindrome(9, i);
      }
    }
    printf("\n");

    // Base 10
    printf("Base %d\n", 10);
    puts("---- --");
    for (uint32_t i = 0; i < bv_get_len(bv); i++) {
      if (bv_get_bit(bv, i)) {
        palindrome(10, i);
      }
    }
    printf("\n");

    // Base 32
    printf("Base %d\n", 32);
    puts("---- --");
    for (uint32_t i = 0; i < bv_get_len(bv); i++) {
      if (bv_get_bit(bv, i)) {
        palindrome(32, i);
      }
    }
    printf("\n");
  }

  bv_delete(bv);
  return 0;
}

void palindrome(uint32_t to_base, uint32_t prime) {
  int const len = (int)(log(prime) / log(to_base)) + 2;
  char *str = (char *)malloc(sizeof(char) * len);
  if (!str) {
    puts("Error: failed to allocate string on heap.");
    return;
  }

  uint32_t quotient = prime, remainder = 0;
  for (int i = 0; i < len - 1; i++) {
    remainder = quotient % to_base;
    if (remainder > 9) {
      str[i] = remainder + 87; // ASCII 97 = 'a'
    } else {
      str[i] = remainder + 48; // ASCII 48 = '0'
    }
    quotient /= to_base;
  }
  str[len - 1] = '\0';

  bool res = true;
  for (int i = 0; i < (len / 2); i++) {
    if (str[i] != str[len - i - 2]) {
      res = false;
      break;
    }
  }

  if (res) {
    printf("%d = %s\n", prime, str);
  }

  free(str);
  return;
}
