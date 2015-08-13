/* fix the mod function */
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<gmp.h>
#include<gmpxx.h>
#include<assert.h>
#include <iostream>

#define BILLION 1000000000L

void mod(mpf_class, mpf_class, mpf_class);

using namespace std;

int main(int argc, char *argv[]) {
  mpf_class e, n, data;
  uint64_t diff;
  struct timespec start, end;

  e = argv[1];
  n = argv[2];
  data = argv[3];

  /* cout << "e is " << e << endl; */
  /* cout << "n is " << n << endl; */
  /* cout << "data is " << data << endl; */
  
  clock_gettime(CLOCK_MONOTONIC, &start);
  mod(data, e, n);
  clock_gettime(CLOCK_MONOTONIC, &end);

  diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
  printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
  return 0;
}

void mod(mpf_class base, mpf_class exponent, mpf_class den)
{   
  mpz_class a, zbase, zden, ret;
  mpf_class size;
  zbase = base; zden = den; // convert to int
  a = (zbase%zden);
  a = a * a;
  
  size = exponent/2.0; 
  
   if(exponent==0) {  
     ret = zbase % zden; 
   } else {  
     while(1) { 
       if(size>0.5f) { 
	 ret = (ret * a)%zden; 
	 size = size - 1.0f;
       }
       else if (size == 0.5f) {
	 ret = zbase % zden;
	 ret = ret * ret;
	 ret = ret % zden;
	 break;
       }
       else break;
     } 
   } 
}
