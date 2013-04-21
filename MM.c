/* Mitchell-Moore algorithm from
 * The Art of Computer Programming, Volume II, by Donald Knuth */

#include "generators.h"

#define L 37U
#define K 100U

static unsigned long int sequence[K];
static unsigned int a, b;

void init_mm(unsigned long int seed) {
  unsigned int i;

  b = K;
  a = L;

  for (i = 0; i < K * 2; i++)
    sequence[i % K] = seed = (1664525 * seed + 1013904223);

  return;
}


/* Clear version */
unsigned long int rand_mm1(void) {
  if (b == K)
    b = 0;
  else if (a == K)
    a = 0;

  return sequence[b++] += sequence[a++];
}


/* Alternative clear version */
unsigned long int rand_mm2(void) {
  a++;
  b++;
  return sequence[b % K] += sequence[a % K];
}


/* Faster version */
unsigned long int rand_mm(void) {
  return sequence[b = (b == K) ? 0 : b + 1] += sequence[a = (a == K) ? 0 : a + 1];
}
