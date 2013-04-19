/* Mitchell-Moore algorithm from
 * The Art of Computer Programming, Volume II, by Donald Knuth */

#include "generators.h"

#define L 27U
#define K 98U

static unsigned long int rgiState[K];
static unsigned int aState, bState;

void init_mm(unsigned long int seed) {
  unsigned int i;

  bState = K - K;
  aState = K - L;

  for (i = 0; i < K; i++)
    rgiState[i] = seed = (69069 * seed + 1);

  return;
}

unsigned long int rand_mm(void) {
  if (++bState == K)
    bState = 0;

  if (++aState == K)
    aState = 0;

  return (rgiState[bState] += rgiState[aState]) >> 6;
}
