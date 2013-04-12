/* Based on Mitchell-Moore algorithm from
 * The Art of Computer Programming, Volume II, by Donald Knuth */

#include "generators.h"

static unsigned long int rgi[32] = {
  0x00000011, 0x9a319039, 0x32d9c024, 0x9b663182, 0x5da1f342, 0xde3b81e0,
  0xdf0a6fb5, 0xf103bc02, 0x48f340fb, 0x7449e56b, 0xbeb1dbb0, 0xab5c5918,
  0x946554fd, 0x8c2e680f, 0xeb3d799f, 0xb11ee0b7, 0x2d436b86, 0xda672e2a,
  0x1588ca88, 0xe369735d, 0x904f35f7, 0xd7158fd6, 0x6fa6f051, 0x616e6b96,
  0xac94efdc, 0x36413f93, 0xc622c298, 0xf5a42ab8, 0x8a88d77b, 0xf5ad9d0e,
  0x8999220b, 0x27fb47b9
};

static unsigned long int *fp = &rgi[4];
static unsigned long int *rp = &rgi[1];
static unsigned long int *piState = &rgi[1];

unsigned long int rand_mmopt(void) {
  unsigned long int i;
  *fp += *rp;
  i = (*fp >> 1) & 0x7fffffff;
  if (++fp >= &rgi[32]) {
    fp = piState;
    ++rp;
  } else if (++rp >= &rgi[32])
    rp = piState;
  return i >> 6;
}

void init_mmopt(unsigned long int seed) {
  int i = 1;
  piState[0] = seed;
  for (i = 1; i < 31; i++)
    piState[i] = 1103515245 * piState[i - 1] + 12345;
  fp = &piState[3];
  rp = &piState[0];
  for (i = 0; i < 10 * 31; i++)
    rand_mmopt();
  return;
}
