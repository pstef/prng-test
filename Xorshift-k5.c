/* George Marsaglia,
   https://groups.google.com/d/msg/comp.lang.c/qZFQgKRCQGg/rmPkaRHqxOMJ */

#include "generators.h"
#include <stdlib.h>

static unsigned long int x, y, z, w, v;

void init_xorshift_k5(unsigned long int seed) {
  srand48((unsigned int) seed);
  x = (unsigned long int) mrand48();
  y = (unsigned long int) mrand48();
  z = (unsigned long int) mrand48();
  w = (unsigned long int) mrand48();
  v = (unsigned long int) mrand48();
  return;
}

unsigned long int xorshift_k5(void) {
  unsigned long int t = (x ^ (x >> 7));
  x = y;
  y = z;
  z = w;
  w = v;
  v = (v ^ (v << 6)) ^ (t ^ (t << 13));
  return (y + y + 1) * v;
}
