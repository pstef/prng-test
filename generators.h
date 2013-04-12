extern void init_derp(unsigned long int seed);
extern unsigned long int rand_derp(void);

extern void init_LCGk1(unsigned long int seed);
extern unsigned long int LCGk1(void);

extern void init_mm(unsigned long int seed);
extern unsigned long int rand_mm(void);

extern void init_mmopt(unsigned long int seed);
extern unsigned long int rand_mmopt(void);

extern void init_mt(unsigned long int seed);
extern unsigned long int mt_rand(void);

extern void init_MWC256(unsigned long int seed);
extern unsigned long int MWC256(void);

extern void p_srand(unsigned long int seed);
extern unsigned long int p_rand(void);

extern void InitWELLRNG44497a(unsigned long int seed);
extern unsigned long int WELLRNG44497a(void);

extern void InitWELLRNG44497b(unsigned long int seed);
extern unsigned long int WELLRNG44497b(void);

extern void init_well512(unsigned long int seed);
extern unsigned long int WELLRNG512a(void);

extern void init_xorshift_k4(unsigned long int seed);
extern unsigned long int xorshift_k4(void);

extern void init_xorshift_k5(unsigned long int seed);
extern unsigned long int xorshift_k5(void);
