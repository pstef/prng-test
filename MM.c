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

unsigned long int rand_mm(void) {
  if (b++ == K)
    b = 0;

  if (a++ == K)
    a = 0;

  return sequence[b] += sequence[a];
}
