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
* WELL44497a - Well Equidistributed Long-period Linear, k=44497, no tempering
* WELL44497b - WELL, k=44497, with tempering
* WELL512 - WELL, k=512
* Xorshift-k4 by George Marsaglia
* Xorshift-k5 by George Marsaglia

#### References and Links
* Donald Knuth: The Art Of Computer Programming, volume 2, third edition
* Richard Brent's [PRNG implementations](http://maths-people.anu.edu.au/~brent/random.html)
* Richard Brent: [Uniform Random Number Generators for Vector and Parallel Computers](http://maths-people.anu.edu.au/~brent/pd/rpb132tr.pdf)
* Richard Brent: [Uniform random number generators for supercomputers](http://maths-people.anu.edu.au/~brent/pub/pub132.html)
* Richard Brent: [Fast and reliable random number generators](http://maths-people.anu.edu.au/~brent/pub/pub217.html)
* Richard Brent: [Some Long-Period Random Number Generators using Shifts and Xors](http://maths-people.anu.edu.au/~brent/pub/pub224.html)
* Richard Brent: [On the periods of generalized Fibonacci recurrences](http://maths-people.anu.edu.au/~brent/pub/pub133.html)
* Richard Brent: [A Fast Algorithm for Testing Irreducibility of Trinomials mod 2](http://maths-people.anu.edu.au/~brent/pub/pub199.html)
* Richard Brent: [Random number generation and simulation on vector and parallel computers](http://maths-people.anu.edu.au/~brent/pub/pub185.html)
* P. L'Ecuyer: [Tables of Linear Congruential Generators of different sizes and good lattice structure](http://www.iro.umontreal.ca/~lecuyer/myftp/papers/latrules.ps)
* N. Dimopoulos, K. Li: [High performance computing systems and applications](http://books.google.com/books?id=rKM6Vyqp8gYC)
* Hertzberger, Hoekstra, Williams: [High-Performance Computing and Networking](http://books.google.com/books?id=vOE0s6Zfk6gC)
* Robert Ziff: [Four-tap shift-register-sequence random-number generators](http://arxiv.org/pdf/cond-mat/9710104v1.pdf)
* Helmut Katzgraber: [Random Numbers in Scientiﬁc Computing: An Introduction](http://arxiv.org/pdf/1005.4117.pdf)
* Andrew Karl: [Pseudorandom Numbers: Generation, Statistical Measures, Monte Carlo Methods, and Implementation in C++](http://economics.nd.edu/assets/24019/karl_a.pdf)
* [Mersenne numbers](http://oeis.org/A000225)
* [Further references](http://sprng.fsu.edu/Version4.0/refs.html)
