#include "generators.h"

static unsigned long int p_next = 1;

unsigned long int p_rand(void) {
  unsigned long int result;
  /* ANSI-C portable implementation */
  p_next = p_next * 1103515245 + 12345;
  result = p_next & 2147483647;

  /* improve randomness by swapping byte 1 with byte 3 */
  return (result & 2130771712) | ((result & 255) << 16) |
         ((result & 16711680) >> 16);
}

void p_srand(unsigned long int seed) {
  p_next = seed;
  return;
}
