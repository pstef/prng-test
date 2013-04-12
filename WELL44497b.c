/* ****************************************************************************
Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal
                Makoto Matsumoto, Hiroshima University
Notice:         This code can be used freely for personal, academic,
                or non-commercial purposes. For commercial purposes,
                please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca
**************************************************************************** */

#include <stdlib.h>
#include "generators.h"

#define W 32
#define R 1391
#define P 15
#define MASKU (0xffffffffU >> (W - P))
#define MASKL (~MASKU)

#define M1 23
#define M2 481
#define M3 229

#define TEMPERB 0x93dd1400U
#define TEMPERC 0xfa118000U

#define MAT0POS(t, v) (v ^ (v >> t))
#define MAT0NEG(t, v) (v ^ (v << (-(t))))
#define MAT1(v) v
#define MAT3NEG(t, v) (v << (-(t)))
#define MAT5(r, a, ds, dt, v)                                                  \
  ((v & dt) ? ((((v << r) ^ (v >> (W - r))) & ds) ^ a)                         \
            : (((v << r) ^ (v >> (W - r))) & ds))

#define V0            STATE[state_i]
#define VM1Over       STATE[state_i+M1-R]
#define VM1           STATE[state_i+M1]
#define VM2Over       STATE[state_i+M2-R]
#define VM2           STATE[state_i+M2]
#define VM3Over       STATE[state_i+M3-R]
#define VM3           STATE[state_i+M3]
#define Vrm1          STATE[state_i-1]
#define Vrm1Under     STATE[state_i+R-1]
#define Vrm2          STATE[state_i-2]
#define Vrm2Under     STATE[state_i+R-2]

#define newV0         STATE[state_i-1]
#define newV0Under    STATE[state_i-1+R]
#define newV1         STATE[state_i]

enum state {C1, C2, C3, C4, C5, C6};

static unsigned long int STATE[R];
static unsigned long int z0, z1, z2, y;
static int state_i = 0;
static enum state state = C1;

static inline unsigned long int case_1(void);
static inline unsigned long int case_2(void);
static inline unsigned long int case_3(void);
static inline unsigned long int case_4(void);
static inline unsigned long int case_5(void);
static inline unsigned long int case_6(void);

void InitWELLRNG44497b(unsigned long int seed) {
  state_i = 0;
  state = C1;

  unsigned int j;
  srand48((unsigned int) seed);
  for (j = 0; j < R; j++)
    STATE[j] = (unsigned long int) mrand48();

  return;
}

unsigned long int WELLRNG44497b(void) {
  switch (state) {
    case C1: return case_1();
    case C2: return case_2();
    case C3: return case_3();
    case C4: return case_4();
    case C5: return case_5();
    case C6: return case_6();
  }
}

static inline unsigned long int case_1(void) {
  // state_i == 0
  z0 = (Vrm1Under & MASKL) | (Vrm2Under & MASKU);
  z1 = MAT0NEG(-24, V0) ^ MAT0POS(30, VM1);
  z2 = MAT0NEG(-10, VM2) ^ MAT3NEG(-26, VM3);
  newV1 = z1 ^ z2;
  newV0Under = MAT1(z0) ^ MAT0POS(20, z1) ^
               MAT5(9, 0xb729fcecU, 0xfbffffffU, 0x00020000U, z2) ^ MAT1(newV1);
  state_i = R - 1;
  state = C3;

  y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
  y = y ^ ((y << 15) & TEMPERC);

  return y;
}

static inline unsigned long int case_2(void) {
  // state_i == 1
  z0 = (Vrm1 & MASKL) | (Vrm2Under & MASKU);
  z1 = MAT0NEG(-24, V0) ^ MAT0POS(30, VM1);
  z2 = MAT0NEG(-10, VM2) ^ MAT3NEG(-26, VM3);
  newV1 = z1 ^ z2;
  newV0 = MAT1(z0) ^ MAT0POS(20, z1) ^
          MAT5(9, 0xb729fcecU, 0xfbffffffU, 0x00020000U, z2) ^ MAT1(newV1);
  state_i = 0;
  state = C1;

  y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
  y = y ^ ((y << 15) & TEMPERC);

  return y;
}

static inline unsigned long int case_3(void) {
  // state_i+M1 >= R
  z0 = (Vrm1 & MASKL) | (Vrm2 & MASKU);
  z1 = MAT0NEG(-24, V0) ^ MAT0POS(30, VM1Over);
  z2 = MAT0NEG(-10, VM2Over) ^ MAT3NEG(-26, VM3Over);
  newV1 = z1 ^ z2;
  newV0 = MAT1(z0) ^ MAT0POS(20, z1) ^
          MAT5(9, 0xb729fcecU, 0xfbffffffU, 0x00020000U, z2) ^ MAT1(newV1);
  state_i--;
  if (state_i + M1 < R)
    state = C4;

  y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
  y = y ^ ((y << 15) & TEMPERC);

  return y;
}

static inline unsigned long int case_4(void) {
  // state_i+M3 >= R
  z0 = (Vrm1 & MASKL) | (Vrm2 & MASKU);
  z1 = MAT0NEG(-24, V0) ^ MAT0POS(30, VM1);
  z2 = MAT0NEG(-10, VM2Over) ^ MAT3NEG(-26, VM3Over);
  newV1 = z1 ^ z2;
  newV0 = MAT1(z0) ^ MAT0POS(20, z1) ^
          MAT5(9, 0xb729fcecU, 0xfbffffffU, 0x00020000U, z2) ^ MAT1(newV1);
  state_i--;
  if (state_i + M3 < R)
    state = C5;

  y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
  y = y ^ ((y << 15) & TEMPERC);

  return y;
}

static inline unsigned long int case_5(void) {
  //state_i+M2 >= R
  z0 = (Vrm1 & MASKL) | (Vrm2 & MASKU);
  z1 = MAT0NEG(-24, V0) ^ MAT0POS(30, VM1);
  z2 = MAT0NEG(-10, VM2Over) ^ MAT3NEG(-26, VM3);
  newV1 = z1 ^ z2;
  newV0 = MAT1(z0) ^ MAT0POS(20, z1) ^
          MAT5(9, 0xb729fcecU, 0xfbffffffU, 0x00020000U, z2) ^ MAT1(newV1);
  state_i--;
  if (state_i + M2 < R)
    state = C6;

  y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
  y = y ^ ((y << 15) & TEMPERC);

  return y;
}

static inline unsigned long int case_6(void) {
  // 2 <= state_i <= R-M2-1
  z0 = (Vrm1 & MASKL) | (Vrm2 & MASKU);
  z1 = MAT0NEG(-24, V0) ^ MAT0POS(30, VM1);
  z2 = MAT0NEG(-10, VM2) ^ MAT3NEG(-26, VM3);
  newV1 = z1 ^ z2;
  newV0 = MAT1(z0) ^ MAT0POS(20, z1) ^
          MAT5(9, 0xb729fcecU, 0xfbffffffU, 0x00020000U, z2) ^ MAT1(newV1);
  state_i--;
  if (state_i == 1)
    state = C2;

  y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
  y = y ^ ((y << 15) & TEMPERC);

  return y;
}
