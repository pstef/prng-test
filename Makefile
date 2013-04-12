CC=clang
CFLAGS=-ggdb -Weverything -Wno-padded -pedantic -std=c99 -D_XOPEN_SOURCE=500
OBJECTS=derp.o LCG-k1.o MM.o MMopt.o MT19937.o MWC256.o p_rand.o prng-test.o WELL44497a.o WELL44497b.o WELL512.o Xorshift-k4.o Xorshift-k5.o

all: $(OBJECTS)
	@echo "[CC -o] prng-test"
	@rm -f prng-test
	@$(CC) -o prng-test $(OBJECTS) -lm

.c.o:
	@echo "[CC -c] $@"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o prng-test
