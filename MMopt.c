/* Mitchell-Moore algorithm from
 * "The Art of Computer Programming, Volume II"
 * by Donald E. Knuth
 * 
 * Improvements based on
 * "Uniform Random Number Generators for Vector and Parallel Computers"
 * by Richard P. Brent */

#include "generators.h"

#define R 32U
#define S 21U
#define T 12U

static unsigned long int sequence[R];
static unsigned int a = R, b = S, c = T;

void init_mmopt(unsigned long int seed) {
  unsigned int i;

  for (i = 0; i < R * 2; i++)
    sequence[i % R] = seed = (1664525 * seed + 1013904223);

  sequence[0] <<= 1;
  sequence[1] |= 1;

  return;
}

unsigned long int rand_mmopt(void) {
  return sequence[++a % R] += sequence[++b % R] + sequence[++c % R];
}
