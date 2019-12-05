#include<time.h>
#include<limits.h>

static inline void yield(void){

  const char* start_yield = getenv("RAND_YIELD");

  unsigned cycles_high, cycles_low;

  asm volatile ("RDTSCP\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low)::
    "%rax", "%rbx", "%rcx", "%rdx");
  // configure priority (default: static value 90)
  srandom((int)(cycles_low % INT_MAX));

  if(start_yield != NULL && strncmp(start_yield, "1", 1)==0)
  {
   if(random()%2 ==0)
   {
	int i;
	for(i=0; i<1; i++)
	   pthread_yield();
   }
  }
}
