/* From George Marsaglia,
   https://groups.google.com/d/msg/comp.lang.c/qZFQgKRCQGg/rmPkaRHqxOMJ */
#include "generators.h"

static unsigned long int x;

#define W (1UL << 32)
#define M W
#define C 362437
#define A 69069

void init_LCGk1(unsigned long int seed) {
  x = seed;
}

unsigned long int LCGk1(void) {
  return x = (A * x + C) % M;
}

/*
The following is more of a summary than my own reaserch. Most of it is copied from Knuth and others; I only reorganized their conclusions to understand LCGs better.

Linear congruential generators are in the general form: X1 = (A * X0 + C) % M, where:
W is computer's word size, for example 8 bits
P is the largest prime that fits in W
M is W, or W+-1, or P
C is either 0 or a positive integer relatively prime to M
A is a primitive element modulo M
X1 is the next sequence member after X0 (that is, the generated pseudo-random number)
X0 is the current member of the sequence; the first one is given by the user and is called the seed.
   It's usually arbitrary, unless C = 0, in which case X0 has to be relatively prime to M

Choosing the parameters of an LCG usually begins with choosing the M, and there are the following 3 choices:

Option I: M = W (computer's word size)
  * Implementations don't need to perform the modulo operation
  * The lower bits are much less random than the higher bits

  1. C is preferred to be relatively prime to M, because that guarantees the longest period possible
  2. The requirement that A is a primitive element modulo M simplifies to:
  a) B = A - 1 is a multiple of P, for every prime P dividing M
  b) B is a multiple of 4 if M is a multiple of 4

  #define W 256
  #define M W
  #define C 1
  #define A 5

Option II: M = P (largest prime not greater than W)
(When C = 0 and M = P, this variant of LCGs is known as Lehmer PRNG or Park-Miller PRNG.)
  * Every bit is equally random
  * Slower than Option I, as it requires modulo operation

  1. C is preferred to be relatively prime to M, because that guarantees the longest period possible
  2. The requirement that A is a primitive element modulo M simplifies to:
  a) A is a primitive root modulo M, since M is a prime

  #define W 256
  #define P 251
  #define M P
  #define C 1
  #define A 6

Option III: M = W +- 1
  * Every bit is equally random
  * Slower than Option I, but faster than Option II at least when implemented on the theoretical computer MIX
  * Since C = 0 is preferred, this variant has shorter period

  1. C is preferred to be 0, because for most of popular word sizes, W+-1 is generally not divisible by high powers of primes, so a high potency is impossible. The maximum-period method should not be used.
  2. X0 is relatively prime to M
  3. A is a primitive element modulo M. Candidates for primitive element modulo N are all elements of the group (all integers relatively prime to N, not greater than N). The elements of the highest order are primitive.

  #define W 256
  #define M (W - 1)
  #define C 0
  #define A 3
  #define X0 2
*/
