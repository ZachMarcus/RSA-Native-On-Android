#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

void mod(int *,int,int,int);

void main(int argc, char *argv[]) {
	int e = strtol(argv[1],NULL,0);
	int n = strtol(argv[2],NULL,0);
	char *data_in = argv[3];
	int length = sizeof(data_in)/sizeof(data_in[0]);
	int *data = (int*)malloc(length*sizeof(int));
	clock_t begin, end;
	
	int i;
	for(i = 0; i < length; i++) data[i] = data_in[i] - '0';

	begin = clock();
	mod(data, e, n, length);
	end = clock();

	printf("%f\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

void mod(int (*base), int exponent, int den, int length)
{   
	int i;
	for(i=0;i<length;i++) {
		unsigned int a=(base[i]%den)*(base[i]%den);
		unsigned long int ret=1;
		float size = (float)exponent/2;
		
		if(exponent==0) ret=base[i]%den;
		else {
			while(1) {
				if(size>0.5f) {
					ret=(ret*a)%den;
					size=size-1.0f;
				}
				else if(size==0.5f) {
					ret=(ret*(base[i]%den))%den;
					break;
				}
				else break;
			}
		}
	}
}
