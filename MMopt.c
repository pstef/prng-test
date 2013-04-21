/* Mitchell-Moore algorithm from
 * The Art of Computer Programming, Volume II, by Donald Knuth
 * 
 * Improvements based on "Uniform Random Number Generators for Vector
 * and Parallel Computers" by Richard P. Brent */

#include "generators.h"

#define R 128U
#define S 82U
#define T 53U

static unsigned long int sequence[R];
static unsigned int a, b, c;

void init_mmopt(unsigned long int seed) {
  unsigned int i;

  a = R - R;
  b = R - S;
  c = R - T;

  for (i = 0; i < R * 2; i++)
    sequence[i % R] = seed = (1664525 * seed + 1013904223);

  sequence[0] <<= 1;
  sequence[1] |= 1;

  return;
}

unsigned long int rand_mmopt(void) {
  return sequence[++a & 127] += sequence[++b & 127] + sequence[++c & 127];
}
