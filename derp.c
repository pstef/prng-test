/* This little device is something I've figured out myself, quite randomly. Its
 * name reflects how much thought I put into it. */

#include "generators.h"

static unsigned long int derp;

void init_derp(unsigned long int seed) {
  derp = seed + 0xABadC0de;
}

unsigned long int rand_derp(void) {
  return (derp += 0xABadC0de) >> 2;
}
