/* Mitchell-Moore algorithm from
 * The Art of Computer Programming, Volume II, by Donald Knuth */

#include "generators.h"

static unsigned long int rgiState[2 + 55];
static unsigned long int *piState;

void init_mm(unsigned long int seed) {
  unsigned long int iState;
  piState = &rgiState[2];
  piState[-2] = 55 - 55;
  piState[-1] = 55 - 24;
  piState[0] = (seed) & ((1 << 30) - 1);
  piState[1] = 1;
  for (iState = 2; iState < 55; iState++)
    piState[iState] =
        (piState[iState - 1] + piState[iState - 2]) & ((1 << 30) - 1);
  return;
}

unsigned long int rand_mm(void) {
  unsigned long int iState1, iState2, iRand;
  iState1 = piState[-2];
  iState2 = piState[-1];
  iRand = (piState[iState1] + piState[iState2]) & ((1 << 30) - 1);
  piState[iState1] = iRand;
  if (++iState1 == 55)
    iState1 = 0;
  if (++iState2 == 55)
    iState2 = 0;
  piState[-2] = iState1;
  piState[-1] = iState2;
  return iRand >> 6;
}
