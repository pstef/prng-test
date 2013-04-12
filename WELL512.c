/* ****************************************************************************
Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal
                Makoto Matsumoto, Hiroshima University
Notice:         This code can be used freely for personal, academic,
                or non-commercial purposes. For commercial purposes,
                please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca
**************************************************************************** */
#include <stdlib.h>
#include "generators.h"

#define R 16U
#define M1 13
#define M2 9

#define M0P(t, v) (v ^ (v >> t))
#define M0N(t, v) (v ^ (v << (t)))
#define M3N(t, v) (v << (t))
#define M4N(t, b, v) (v ^ ((v << (t)) & b))

#define V0 *current
#define VM1 STATE[(state_i + M1) & 0x0FU]
#define VM2 STATE[(state_i + M2) & 0x0FU]
#define VRm1 STATE[(state_i + 15) & 0x0FU]
#define newV0 STATE[(state_i + 15) & 0x0FU]
#define newV1 *current

static unsigned long int STATE[R];

void init_well512(unsigned long int seed) {
  unsigned int j;
  srand48((unsigned int) seed);
  for (j = 0; j < R; j++)
    STATE[j] = (unsigned long int) mrand48();
  return;
}

unsigned long int WELLRNG512a(void) {
  static unsigned long int state_i;
  register unsigned long int z0, z1, z2;
  register unsigned long int *current = &STATE[state_i];
  z0 = VRm1;
  z1 = M0N(16, V0) ^ M0N(15, VM1);
  z2 = M0P(11, VM2);
  newV1 = z1 ^ z2;
  newV0 = M0N(2, z0) ^ M0N(18, z1) ^ M3N(28, z2) ^ M4N(5, 0xda442d24U, newV1);
  state_i = (state_i + 15) & 0x0FU;
  return STATE[state_i];
}
