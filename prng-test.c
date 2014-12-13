#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/time.h>
#include "generators.h"

#define NELEM(array) ((sizeof array) / (sizeof array[0]))

static void options(int argc, char *argv[]);

static struct {
  FILE *output;
  bool binary;
  bool list_only;
  char const *generator_name;
  unsigned long int chunks;
  unsigned long int seed;
} Options;

int main(int argc, char *argv[]) {
  options(argc, argv);

  typedef unsigned long int(generator)(void);
  typedef void(initializer)(unsigned long int);

  struct stats {
    double time;
  };

  struct entry {
    struct stats stats;
    char const *const name;
    generator *const g;
    initializer *const init;
  };

  struct entry prngs[] = {
    { { 0 }, "derp", rand_derp, init_derp },
    { { 0 }, "LCG-k1", LCGk1, init_LCGk1 },
    { { 0 }, "MM", rand_mm, init_mm },
    { { 0 }, "MMopt", rand_mmopt, init_mmopt },
    { { 0 }, "MT19937", mt_rand, init_mt },
    { { 0 }, "MWC256", MWC256, init_MWC256 },
    { { 0 }, "p_rand", p_rand, p_srand },
    { { 0 }, "WELL44497a", WELLRNG44497a, InitWELLRNG44497a },
    { { 0 }, "WELL44497b", WELLRNG44497b, InitWELLRNG44497b },
    { { 0 }, "WELL512", WELLRNG512a, init_well512 },
    { { 0 }, "Xorshift-k4", xorshift_k4, init_xorshift_k4 },
    { { 0 }, "Xorshift-k5", xorshift_k5, init_xorshift_k5 },
  };

  if (Options.list_only) {
    unsigned int i = NELEM(prngs);
    while (i--) {
      fprintf(stderr, "%s\n", prngs[i].name);
    }
    exit(EXIT_SUCCESS);
  }

  if (Options.binary) {
    unsigned int i;
    for (i = 0; i < NELEM(prngs); i++) {
      if (!strcasecmp(Options.generator_name, prngs[i].name))
        break;
    }
    if (i == NELEM(prngs)) {
      fprintf(stderr,
              "Generator \"%s\" not found. "
              "Type \"%s -l\" to get list of all generators.\n",
              Options.generator_name, argv[0]);
      exit(EXIT_FAILURE);
    }
    prngs[i].init(Options.seed);
    unsigned long int j = Options.chunks;
    struct timeval before, after;
    gettimeofday(&before, NULL);
    while (Options.chunks == 0 || j--) {
      uint32_t chunk = (uint32_t) prngs[i].g();
      if (1 > fwrite(&chunk, sizeof chunk, 1, Options.output)) {
        fprintf(stderr, "Error writing to file.\n");
        exit(EXIT_FAILURE);
      }
    }
    gettimeofday(&after, NULL);
    fprintf(stderr, "Generating %lu random numbers with %s took %f seconds.\n",
            Options.chunks, Options.generator_name,
            ((after.tv_sec * 1000000 + after.tv_usec) -
             (before.tv_sec * 1000000 + before.tv_usec)) / 1000000.0);
    exit(EXIT_SUCCESS);
  }
  return 0;
}

static void options(int argc, char *argv[]) {
  int c;
  extern char *optarg;
  extern int optopt;
  Options.output = stdout;
  Options.chunks = 1024 * 1024UL;
  Options.seed = 1;

  if (argc < 2) {
    goto help;
  }

  while ((c = getopt(argc, argv, ":hlo:s:bg:n:")) != -1) {
    switch (c) {
      help:
      case 'h':  //-h help
        fprintf(stderr,
                "  -h help\n"
                "  -l list all generators and exit\n"
                "  -g select one generator\n"
                "  -b don't make built-in tests, generate binary instead\n"
                "  -s use external seed; -s `date +'%%s'` is a nice example\n"
                "  -n generate n 32-bit numbers\n"
                "  -o output to file instead of stdout\n");
        exit(EXIT_SUCCESS);
      case 'l':  //-l list all generators and exit
        Options.list_only = true;
        break;
      case 'g':  //-g select one generator
        Options.generator_name = optarg;
        break;
      case 'b':  //-b don't make built-in tests, generate binary instead
        Options.binary = true;
        break;
      case 's':    //-s use external seed; -s `date +'%s'` is a nice example
      case 'n': {  //-n how many 32-bit numbers
        char *endptr;
        errno = 0;
        unsigned long int number = strtoul(optarg, &endptr, 10);
        if (errno != 0 || *endptr != '\0') {
          fprintf(stderr,
                  "Unable to convert text \"%s\" into a positive number within supported range.\n",
                  optarg);
          exit(EXIT_FAILURE);
        }
        switch (c) {
          case 's':
            Options.seed = number;
            break;
          case 'n':
            Options.chunks = number;
            break;
        }
        break;
      }
      case 'o':  //-o output file
        Options.output = fopen(optarg, "w");
        if (NULL == Options.output) {
          fprintf(stderr, "Unable to open file \"%s\".\n", optarg);
          exit(EXIT_FAILURE);
        }
        break;
      case ':':
        fprintf(stderr, "-%c requires an argument.\n", optopt);
        break;
      case '?':
        fprintf(stderr, "Unknown option %c.\n", optopt);
        break;
    }
  }
  if (Options.binary && !Options.generator_name) {
    fprintf(stderr, "Option -b requires option -g.\n");
    exit(EXIT_FAILURE);
  }
}
