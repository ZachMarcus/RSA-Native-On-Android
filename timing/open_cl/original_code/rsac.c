#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
//#include <windows.h> 

long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
int prime(long int);
void ce();

long int cd(long int);
//void encrypt( int *, int *,int *, int * );
void mod(int *,int,int,int);
int length=4096;
int *buf;
//printf("enter the length of data to encrypt");
//scanf("%d",&length);


long GetTickCount() {
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0) {
		return 0;
	}
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}



void main()
{
//clrscr();
clock_t begin, end;
double time_spent;
begin = clock();
long te, ts;
//int length1=800;
//int key,den;
int  result,dev_key,dev_den;
//int  *result,*dev_key,*dev_den;

//dev_key= &key;
//dev_den= &den;


printf("\nENTER FIRST PRIME NUMBER\n");
scanf("%d",&p);
flag=prime(p);
if(flag==0)
{
    printf("\nWRONG INPUT\n");
    //getch();
    exit(1);
}
printf("\nENTER ANOTHER PRIME NUMBER\n");
scanf("%d",&q);
flag=prime(q);
if(flag==0||p==q)
{
    printf("\nWRONG INPUT\n");
  //  getch();
    exit(1);
} 

int length;
printf("enter the length of data to encrypt");
scanf("%d",&length);
int length1 =800;
		// seed random number generator
		srand(GetTickCount());
		buf = (int*)malloc(length*sizeof(int));

		 for ( i = 0; i < length; i++ )
			{
				 buf [i] = rand ( )%length1;
			}
			for ( i = 0; i < length; i++ )
			{
				 printf("\t%d",buf [i]);
			}

n=p*q;
t=(p-1)*(q-1);
ce();
printf("\nPOSSIBLE VALUES OF e AND d and n ARE\n");
for(i=0;i<j-1;i++)
printf("\n%ld\t%ld\t%ld",e[i],d[i],n);
// ENTER KEY VALUE

		printf("\nEnter key parameter e from above set of values 1:");
	    scanf("%d",&dev_key);
        printf("\nEnter key parameter n from above set of values 2:");
        scanf("%d",&dev_den);
ts = GetTickCount();
mod(buf, dev_key,dev_den, result);
// STOP CLOCK
	end = clock();
    te = GetTickCount();

// show the count difference
	printf("%d ms\n", te - ts);


time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("Time=%f",time_spent); 
printf("\nexit successfully");
//getch();
}

int prime(long int pr)
{
int i;
j=sqrt(pr);
for(i=2;i<=j;i++)
{
    if(pr%i==0)
    return 0;
}
return 1;
}
void ce()
{
int k;
k=0;
for(i=2;i<t;i++)
{
    if(t%i==0)
    continue;
    flag=prime(i);
    if(flag==1&&i!=p&&i!=q)
    {
        e[k]=i;
        flag=cd(e[k]);
        if(flag>0)
        {
            d[k]=flag;
            k++;
        }
        if(k==99)
        break;
    }
}
}
long int cd(long int x)
{
long int k=1;
while(1)
{
    k=k+t;
    if(k%x==0)
    return(k/x);
}
}

void mod(int (*base),int exponent,int den, int ret)
{   //printf("\nin mod");
	for(i=0;i<length;i++)
	{
	//printf("\ni=%d",i);
	unsigned int a=(base[i]%den)*(base[i]%den);
	unsigned long int ret=1;
	float size=(float)exponent/2;
	if(exponent==0)
	{
		ret=base[i]%den;
	}
	else
	{
		while(1)
		{
			if(size>0.5f)
			{
				ret=(ret*a)%den;
				size=size-1.0f;
			}
			else if(size==0.5f)
			{
			ret=(ret*(base[i]%den))%den;
			break;
			}
			else
			{
				break;
			}
		}
		
   
	}
	
	}
	for(i=0;i<length;i++)
	//printf("\t%d",base[i]);
	//printf("\nexit from mod");
}

 
