/* Marsaglia, George (July 2003). "Xorshift RNGs".
 * Journal of Statistical Software. Vol. 8 (Issue  14). */

#include "generators.h"
#include <stdlib.h>

static unsigned long int x, y, z, w;

void init_xorshift_k4(unsigned long int seed) {
  srand48((unsigned int) seed);
  x = (unsigned long int) mrand48();
  y = (unsigned long int) mrand48();
  z = (unsigned long int) mrand48();
  w = (unsigned long int) mrand48();
  return;
}

unsigned long int xorshift_k4(void) {
  unsigned long int t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}
