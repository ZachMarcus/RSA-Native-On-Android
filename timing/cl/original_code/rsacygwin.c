//#include <C:/Program Files/AMD APP/include/CL/cl.h>
//#include <C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v5.5/include/CL/cl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//#include <windows.h> 
//#include<conio.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>
#include <CL/cl.h>


#define MAX_SOURCE_SIZE (0x100000)
// DECLARE GLOBALLY

int length =512;
int * buf;
int *dev_key,*dev_den;

 //DECLARATION FOR e,d and n

long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
char msg[100];
int prime(long int);
void ce();
long int cd(long int); 


//My implementation of GetTickCount()
//This code was written in Windows and this function is usually available in the
//windows.h include file
#include <sys/time.h>

long GetTickCount() {
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0) {
		return 0;
	}
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}



//MAIN STARTS

int main() {
    printf("shreshtha");
	    printf("welcome");
	    char build_c[4096];
		//char *program_log;
		clock_t begin, end;
		double time_spent;
		begin = clock();
		cl_int error;
        cl_platform_id platform;
        cl_device_id device;
        cl_uint platforms, devices;
        long te, ts;
		size_t srcsize,worksize=length*sizeof(int);
		int i;
		int key=5;
		int den=7;
		dev_key= &key;
		dev_den= &den;
		//int devcount;
		int length1=800;

		
		// seed random number generator
		srand(GetTickCount());
		buf = (int*)malloc(worksize);

		 for ( i = 0; i < length; i++ )
			{
				 buf [i] = rand ( )%length1;
			}

	   // Fetch the Platform and Device IDs; we only want one.

	    error=clGetPlatformIDs(1, &platform, &platforms);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
        
        error=clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &devices);
		 //error=clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, device, NULL);
        if (error != CL_SUCCESS)
        {
                printf("\n Error number %d", error);
		}


//calculating e and d


system("cls");
printf("\nENTER FIRST PRIME NUMBER\n");
scanf("%ld",&p);
flag=prime(p);
if(flag==0)
{
    printf("\nWRONG INPUT\n");
    //getch();
    exit(1);
}
printf("\nENTER ANOTHER PRIME NUMBER\n");
scanf("%ld",&q);
flag=prime(q);
if(flag==0||p==q)
{
    printf("\nWRONG INPUT\n");
    //getch();
    exit(1);
}
fflush(stdin);
n=p*q;
t=(p-1)*(q-1);
ce();
printf("\nPOSSIBLE VALUES OF e AND d AND n ARE\n");
for(i=0;i<j-1;i++)
printf("\n%ld\t%ld \t%d",e[i],d[i],n); 
//size_t length2;
        

// ENTER KEY VALUE

		printf("\nEnter key parameter e from above set of values 1:");
	    scanf("%d",dev_key);
        printf("\nEnter key parameter n from above set of values 2:");
        scanf("%d",dev_den);
		//int *dev_num,*dev_key,*dev_den;
		
		//unsigned int *dev_res;
		//unsigned  int res[3]={1,1,1}; BUF2 IS SERVING ITS WORK....
cl_context_properties properties[]={
                CL_CONTEXT_PLATFORM, (cl_context_properties)platform,
               0};
// CREATE CONTEXT
//printf("hi");
	  cl_context context=clCreateContext(properties, 1, &device, NULL, NULL, &error);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

//CREATE COMMAND QUEUE        
        cl_command_queue cq = clCreateCommandQueue(context, device, 0, &error);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
//CREATE FILE
		 FILE *fil=fopen("rsa.cl","r");
		 char *src;
         src = (char *)malloc(MAX_SOURCE_SIZE);
         srcsize=fread(src, 1, MAX_SOURCE_SIZE, fil);
		 fclose(fil);
		const char *srcptr[]={src};

// Submit the source code of the example kernel to OpenCL

		  cl_program prog=clCreateProgramWithSource(context, 1, srcptr, &srcsize, &error);
        if (error != CL_SUCCESS) 
        {
                  printf("\n Error number %d", error);
        }
//error=0;
// and compile it (after this we could extract the compiled version)
//printf("hi");
        error=clBuildProgram(prog, 1, &device, NULL, NULL, NULL);
		 //error=clBuildProgram(prog, 0, NULL, "", NULL, NULL);
        //printf("2");
		
        
        if ( error != CL_SUCCESS ) {
             //printf("3");
                printf( "Error on buildProgram " );
                printf("\n Error number %d", error);
                //printf("4");
                fprintf( stdout, "\nRequestingInfo\n" );
                //printf("5");
                clGetProgramBuildInfo( prog, device, CL_PROGRAM_BUILD_LOG, 4096, build_c, NULL );
				
				
				//program_log = (char*)malloc(length2+1);
				//program_log[length2] = '\0' ;
				//clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG, length2+1, program_log, NULL);
                //printf("6");
                printf( "Build Log for %s_program:\n%s\n", "example",build_c );
				//free(program_log);
				//exit(1);
        }
        //printf("1");

    ts = GetTickCount();

// Allocate memory for the kernel to work with
        cl_mem mem1, mem2, mem3,mem4;
        
        mem1=clCreateBuffer(context, CL_MEM_READ_WRITE, worksize, NULL, &error);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
        
        mem2=clCreateBuffer(context, CL_MEM_READ_WRITE, worksize, NULL, &error);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

		mem3=clCreateBuffer(context,  CL_MEM_READ_WRITE, worksize, NULL, &error);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

		mem4=clCreateBuffer(context,  CL_MEM_READ_WRITE, worksize, NULL, &error);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

		
// get a handle and map parameters for the kernel
        cl_kernel k_example=clCreateKernel(prog, "RSA", &error);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
        
        error = clSetKernelArg(k_example, 0, sizeof(mem1), &mem1);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
        
        error = clSetKernelArg(k_example, 1, sizeof(mem2), &mem2);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

		error = clSetKernelArg(k_example, 2, sizeof(mem3), &mem3);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

		error = clSetKernelArg(k_example, 3, sizeof(mem4), &mem4);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }



// Target buffer just so we show we got the data from OpenCL
        
        int buf2[262144];

// Send input data to OpenCL (async, don't alter the buffer!)
        
        error=clEnqueueWriteBuffer(cq, mem1, CL_FALSE, 0, worksize, buf, 0, NULL, NULL);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

		 error=clEnqueueWriteBuffer(cq, mem2, CL_FALSE, 0, worksize, dev_key, 0, NULL, NULL);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

		 error=clEnqueueWriteBuffer(cq, mem3, CL_FALSE, 0, worksize, dev_den, 0, NULL, NULL);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
        
// Perform the operation
        
        const size_t global_worksize=length;
        error=clEnqueueNDRangeKernel(cq, k_example, 1, NULL, &global_worksize, NULL, 0, NULL, NULL);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
        
// Read the result back into buf2
        
        error=clEnqueueReadBuffer(cq, mem4, CL_FALSE, 0, worksize, buf2, 0, NULL, NULL);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }
        
// Await completion of all the above
        
        error=clFinish(cq);
        if (error != CL_SUCCESS) {
                printf("\n Error number %d", error);
        }

 // Finally, output out happy message.
       /* 
        for(i=0;i<length;i++)
        {
           printf("\n%d",buf2[i]);
           }  */
// STOP CLOCK
	end = clock();
    te = GetTickCount();

// show the count difference
	printf("%d ms\n", te - ts);


time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("Time=%f",time_spent); 

}


//functions for e and d

int prime(long int pr)
{
int i;
j=sqrt((double)pr);
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
        flag= cd(e[k]);
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

