prng-test
=========
### A program for benchmarking and testing pseudo-random generators for use in computer RPGs.

#### When considering a PRNG for a game, I'm interested in the following set of qualities:
* general quality of randomness
* cost, measured in CPU cycles
* ease of use, speed, and elegance of generating well distributed numbers from ranges which have bounds that are not powers of two (20-80, 1-100). All tests I know are based on n-byte chunks of random data. In games, more often than not, a number from a custom range is needed, obtaining which is usually done by applying modulo operation (or more properly something like this: rand() / (RAND_MAX / N + 1)) on a given chunk. This works for some generators, but for others does not and inelegant workarounds are needed (while-loops that keep running until a number from the desired range is found, byte-shifting to avoid sequences of shorter period, etc.).
* quality of randomness in the case of multiple consumers simultaneously fetching numbers from a generator, which is the standard pattern in multiplayer computer games

Some of the above qualities can be measured with existing programs (ent, dieharder), some of them cannot. My plan is to write my own test that will complement the ones that already exist.

#### What's done:
* I've adapted a few implementations of PRNGs, including Mersenne-Twister, WELL, Xorshift, and Mitchell-Moore
* the program can produce a stream of pseudo-random numbers, which is handy for testing quality of a PRNG with an external program, such as ent or dieharder.

#### Currently supported options:
- h: help
- l: list all generators and exit
- g: select one generator
- b: don't make built-in tests, generate binary instead
- s: use external seed; -s \`date +'%s'\` is a nice example
- n: generate n 32-bit numbers
- o: output to file instead of stdout

#### Currently implemented generators:
* derp - a number generator of extremely poor quality, but fast and, apparently, well distributed
* LGC-k1 - a fast Linear Congruential Generator as described by George Marsaglia
* MM - Mitchell-Moore from The Art of Computer Programming by Donald E. Knuth
* MMopt - A slightly different implementation of Mitchell-Moore
* MT19937 - Mersenne-Twister
* MWC256 by George Marsaglia
* p_rand - some LGC I know from Jon Lambert
* WELL44497a - Well Equidistributed Long-period Linear, k=44498, no tempering
* WELL44497b - WELL, k=44498, tempered
* WELL512 - WELL, k=513
* Xorshift-k4 by George Marsaglia
* Xorshift-k5 by George Marsaglia
