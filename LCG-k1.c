/* From George Marsaglia,
   https://groups.google.com/d/msg/comp.lang.c/qZFQgKRCQGg/rmPkaRHqxOMJ */
#include "generators.h"

static unsigned long int x;

void init_LCGk1(unsigned long int seed) { x = seed; }
unsigned long int LCGk1(void) { return (x = 69069 * x + 362437); }
