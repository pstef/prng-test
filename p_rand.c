#include "generators.h"

static unsigned long int p_next = 1;

unsigned long int p_rand(void) {
  /* ANSI-C portable implementation */
  p_next = p_next * 1103515245 + 12345;

  /* improve randomness by swapping byte 1 with byte 3 */
  return (p_next & 0xFF00FF00) | ((p_next & 0x000000FF) << 16) | ((p_next & 0x00FF0000) >> 16);
}

void p_srand(unsigned long int seed) {
  p_next = seed;
  return;
}
