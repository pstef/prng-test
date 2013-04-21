/* Mitchell-Moore algorithm from
 * The Art of Computer Programming, Volume II, by Donald Knuth */

#include "generators.h"

static inline unsigned long int rand_mm1(void);
static inline unsigned long int rand_mm2(void);
static inline unsigned long int rand_mm3(void);

#define L 37U
#define K 100U

static unsigned long int sequence[K];
static unsigned int b, a;

void init_mm(unsigned long int seed) {
  unsigned int i;

  a = K;
  b = L;

  for (i = 0; i < K * 2; i++)
    sequence[i % K] = seed = (1664525 * seed + 1013904223);

  return;
}

/* This way I export one of the implementations below */
unsigned long int rand_mm(void) {
  return rand_mm3();
}


/* Implementations of the algorithm: */

/* Clear version */
static inline unsigned long int rand_mm1(void) {
  if (a == K)
    a = 0;
  else if (b == K)
    b = 0;

  return sequence[a++] += sequence[b++];
}

/* Alternative clear version */
static inline unsigned long int rand_mm2(void) {
  a++;
  b++;
  return sequence[a % K] += sequence[b % K];
}

/* Faster version */
static inline unsigned long int rand_mm3(void) {
  return sequence[a = (a == K) ? 0 : a + 1] += sequence[b = (b == K) ? 0 : b + 1];
}
