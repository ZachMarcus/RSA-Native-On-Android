#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

#define BILLION 1000000000L

void mod(int,int,int);

int main(int argc, char *argv[]) {
	int e = strtol(argv[1],NULL,0);
	int n = strtol(argv[2],NULL,0);
	int data = strtol(argv[3],NULL,2);

	uint64_t diff;
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);
	mod(data, e, n);
	clock_gettime(CLOCK_MONOTONIC, &end);

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
	return 0;
}

void mod(int base, int exponent, int den)
{   
	unsigned int a=(base%den)*(base%den);
	unsigned long int ret=1;
	float size = (float)exponent/2;

	if(exponent==0) ret=base%den;
	else {
		while(1) {
			if(size>0.5f) {
				ret=(ret*a)%den;
				size=size-1.0f;
			}
			else if(size==0.5f) {
				ret=(ret*(base%den))%den;
				break;
			}
			else break;
		}
	}
}
