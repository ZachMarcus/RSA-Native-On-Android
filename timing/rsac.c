#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

void mod(int,int,int);

void main(int argc, char *argv[]) {
	int e = strtol(argv[1],NULL,0);
	int n = strtol(argv[2],NULL,0);
	int data = strtol(argv[3],NULL,2);
	clock_t begin, end;

	begin = clock();
	mod(data, e, n);
	end = clock();

	printf("%d,%f\n", (int)(end - begin), (double)(end - begin) / CLOCKS_PER_SEC);
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
