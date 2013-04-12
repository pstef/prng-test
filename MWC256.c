/* George Marsaglia,
   https://groups.google.com/d/msg/comp.lang.c/qZFQgKRCQGg/rmPkaRHqxOMJ */

#include <stdlib.h>
#include "generators.h"

/* choose random initial c<809430660 and 256 random 32-bit integers for Q[] */
static unsigned long int Q[256], c = 362436;

void init_MWC256(unsigned long int seed) {
  unsigned int j = sizeof Q / sizeof Q[0];
  srand48((unsigned int) seed);
  while (j--) {
    Q[j] = (unsigned long int) mrand48();
  }
  return;
}

unsigned long int MWC256(void) {
  unsigned long int long t, a = 809430660LL;
  static unsigned char i = 255;
  t = a * Q[++i] + c;
  c = (t >> 32);
  return (Q[i] = t);
}
