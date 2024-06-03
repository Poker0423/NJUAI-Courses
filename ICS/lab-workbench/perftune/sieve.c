#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
 

#define N 10000000

static uint8_t is_prime[N / 8 + 1] = {};  // Use bit array instead of bool array
static int primes[N];

float my_fabs(float x) {
  return (x < 0) ? -x : x;
}

float my_sqrt(float n){
  float guess = n;
  while (my_fabs(guess * guess - n) >= 0.25){
    guess = (guess + n / guess) / 2.0;
  }
  return guess;
}

int *sieve(int n) {
  assert(n + 1 < N);
  memset(is_prime, 0xFF, sizeof(is_prime));  // Use memset to initialize bit array
  is_prime[0] &= ~0x01;  // Set 0 to false

  int sqrt_n = my_sqrt(n);  // Calculate square root of n outside the loop

  for (int i = 3; i <= sqrt_n; i += 2) {  // Iterate up to square root of n
    if(is_prime[i >> 3] & (1 << (i & 7))){  // Use bit operation to check if i is prime
      for (int j = i * i; j <= n; j += i << 1) {  // Start from i^2 and increment by 2*i
        is_prime[j >> 3] &= ~(1 << (j & 7));  // Use bit operation to set j to false
      }
    }
  }

  int *p = primes;
  *p++ = 2;
  for (int i = 3; i <= n; i += 2)
    if (is_prime[i >> 3] & (1 << (i & 7))) {  // Use bit operation to check if i is prime
      *p++ = i;
    }
  *p = 0;
  return primes;
}

