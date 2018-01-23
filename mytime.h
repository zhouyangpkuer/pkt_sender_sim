#ifndef _MYTIME_H
#define _MYTIME_H
#include <sys/types.h>
#include <sys/sysctl.h>

using namespace std;

#define u64 unsigned long
#define u32 unsigned int 
#define u16 unsigned short 
#define u8 unsigned char 
#define always_inline inline __attribute__((always_inline))



#define TSC_FREQ (2.5e9)

inline unsigned long getTSC()
{ 
  unsigned int __a,__d;  
  asm volatile("rdtsc" : "=a" (__a), "=d" (__d));  
  unsigned long val= ((unsigned long)__a) | (((unsigned long)__d)<<32);  
  return val;
}



always_inline u64
get_tsc_cycles (void)
{
  u32 a, d;
  asm volatile ("rdtsc":"=a" (a), "=d" (d));
  return (u64) a + ((u64) d << (u64) 32);
}


#endif// _TIME_H