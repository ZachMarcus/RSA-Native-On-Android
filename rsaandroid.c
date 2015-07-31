#include <stdio.h>
#include <string.h>
#include <time.h>
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

/*
#ifdef DEBUG
#define LOGD(stmt) \
    printf(stdout, stmt) \
    flush(stdout)
#else
#define LOGD(stmt)
#endif

#define DEBUG*/


long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
char msg[100];
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
int prime(long int pr)
{
    j=sqrt((double)pr);
    for(int i=2;i<=j;i++)
    {
        if(pr%i==0)
        return 0;
    }
    return 1;
}
void ce()
{
    printf("\nEntered ce() function");
    int k = 0;
    for(i=2;i<t;i++)
    {
        /*if(t%j==0) {
            continue;
        }
        printf("\nRunning prime(j)");
        flag=prime(j);
        if(flag==1&&j!=p&&j!=q)
        {
            e[k]=j;
            flag= cd(e[k]);
            if(flag>0)
            {
                d[k]=flag;
                k++;
            }
            if(k==99) {
            break;
            }
        }*/
        if(t % i == 0) {
        }
        else 
        {
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
                if(k==99) {
                    break;
                }
            }
        }
    }
}



//My implementation of GetTickCount() for Linux systems.
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
    printf("Zachary,");
    printf("welcome");
    char build_c[4096];
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
    printf("\nJust fetched PlatformIDs");
    error=clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &devices);
    //error=clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, device, NULL);
    if (error != CL_SUCCESS)
    {
        printf("\n Error number %d", error);
    }
    printf("\nJust fetched DeviceIDs");

    //calculating e and d
    printf("\nENTER FIRST PRIME NUMBER\n");
    scanf("%ld",&p);
    flag=prime(p);
    if(flag==0)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    printf("\nENTER ANOTHER PRIME NUMBER\n");
    scanf("%ld",&q);
    flag=prime(q);
    //printf("\nJust ran the prime function");
    if(flag==0||p==q)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    fflush(stdin);
    n=p*q;
    t=(p-1)*(q-1);
    //printf("\nAbout to run ce() function");
    ce();
    //printf("\nJust ran the ce() function");
    printf("\nPOSSIBLE VALUES OF e AND d AND n ARE\n");
    for(i=0;i<j-1;i++)
    printf("\n%ld\t%ld \t%d",e[i],d[i],(int)n); 

    // ENTER KEY VALUE
    printf("\nEnter key parameter e from above set of values 1:");
    scanf("%d",dev_key);
    printf("\nEnter key parameter n from above set of values 2:");
    scanf("%d",dev_den);
    printf("\nTrying to do something with properties:");


    printf("\nSomething from OpenCL worked!");
    fflush(stdout);
    // CREATE CONTEXT
    cl_context context=clCreateContext(0, 1, &device, NULL, NULL, &error);
    if (error != CL_SUCCESS) {
        printf("\n Error number %d", error);
    }
    printf("\nSuccessful clCreateContext\n");
    //CREATE COMMAND QUEUE        
    cl_command_queue cq = clCreateCommandQueue(context, device, 0, &error);
    if (error != CL_SUCCESS) {
        printf("\n Error number %d", error);
    }

    //CREATE FILE
    printf("\nAbout to open the kernel file");
    fflush(stdout);
    FILE *fil=fopen("rsa.cl","r");
    printf("\nJust opened the kernel file");
    if (fil == NULL) {
    	printf("Error");
        fclose(fil);
        fflush(stdout);
        return -1;
    }
    char *src;
    printf("\nAbout to allocate memory");
    src = (char *)malloc(MAX_SOURCE_SIZE);
    printf("\nAbout to read in from the kernel file");
    srcsize=fread(src, 1, MAX_SOURCE_SIZE, fil);
    printf("\nJust read in from the kernel file");
    fclose(fil);
    fflush(stdout);
    const char *srcptr[]={src};

    // Submit the source code of the example kernel to OpenCL
    cl_program prog=clCreateProgramWithSource(context, 1, srcptr, &srcsize, &error);
    if (error != CL_SUCCESS) 
    {
        printf("\n Error number %d", error);
    }

    // and compile it (after this we could extract the compiled version)
    error=clBuildProgram(prog, 1, &device, NULL, NULL, NULL);
    if ( error != CL_SUCCESS ) {
        printf( "Error on buildProgram " );
        printf("\n Error number %d", error);
        fprintf( stdout, "\nRequestingInfo\n" );
        clGetProgramBuildInfo( prog, device, CL_PROGRAM_BUILD_LOG, 4096, build_c, NULL );
        printf( "Build Log for %s_program:\n%s\n", "example",build_c );
    }

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

    // STOP CLOCK
    end = clock();
    te = GetTickCount();

    // show the count difference
    printf("%d ms\n", (int)(te - ts));
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time=%f",time_spent);
}




