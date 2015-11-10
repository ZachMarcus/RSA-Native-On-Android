
#define __CL_ENABLE_EXCEPTIONS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#include <jni.h>

#include "crypto.h"

void cMain(int numberOfTimes, int c_d, int c_n, int c_key);
void clMain(int numberOfTimes);
void GMPmain(int numberOfTimes);


int main() {
	try {
		//GMPmain(1000);
		clMain(1000);
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	return 0;
}

int * bin_array(mpz_class num);
mpz_class GMPmod(mpz_class &m, mpz_class &exp, mpz_class &n);
void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n);

#define HARDCODED_KEYS 1
#define EXP "158306798557072761079432079748149567825016765046913883964014613775776306037474501463369921628992533312298808609078756097042285249267890219078764623497470192144382514657581587703973692641931288995078102752352350184834385610173615683815147403068520116706643320240742275484768353777145356967526250960072595031109023860493087239629618880211298451357897808581975171080587694389253548071795540933573481163120602186428765592638764414969533247632383239347611397572387560951725016051582947213376518971466490963334721098767600820592472431715518848339987055020980311250201733120122669828244108187929299248552223223894566135545400347395519737305188238745862278377831456612518021279116789394170665428199664514569903444448841288369247960611262064577076902541441590646306319732815527028743410427325307867085533659713405324088567498669018644897978482350367315185541212736392389216659163570687063127142133114283227999573805923235609377191041858837705257557287987683494489939245908739573552554516582936801486538385236278031855734878145407050620095988949937666850728403590671448282858402427230605736136330498082797183589963287248500425533468417140659042008156430852402229291556649868936670281819509988720694760732191525783523778328847496836923703312737"
#define MOD "715958364297486546329634960351561536577746444750506881053731677801604566198189662715124874321943527409297289339120449819326495644280568717670622947357235800328921183018005970143904761208629555370259721211849836040541793508656976818038321396377172237154322219213134118311038824200729781214599952326980723245724387326280826611248798050680275109146542590645014615078909373210165604856894925551280466150537223482988200306726016386989048405912876982756497699448041100137547607271588683425785447783658782572911987899381150712798900404205366003978864924774686816534709197673968629669010704458789765016380308703635234340296713700225706992999441659061943544901181390056235663409008322181462166603323951083429017995004587660272585619764694220034272255338359971389550871726055789666787195714454790017955312813039690435170078343265427018842974067370648439758420373556942410294736075271841522709415144611715775347563980480170739794412780191470182979085746411978862782003998299068558934086783542205382407135682727579619750565064640699779975357623009397403595084526951044861438636676160329372203580148769149922658869071822944571338856466414213283516319832616987526768573589294348111370949186498201244479135082298818427968963158235718319254698242413"
#define FIRST_PRIME "1"
#define SECOND_PRIME "1"
#define KEY_BASE 10

size_t exp_bitsize;
int * bin;


// DECLARE GLOBALLY
int length =512;
int * buf;
int *dev_key,*dev_den;
//DECLARATION FOR e,d and n

long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
char msg[100];


//Continually increments k by t, until k is divisible by x.
//Returns the result of this division.
long int cd(long int x) {
    long int k=1;
    while(1) {
        k=k+t;
        if(k%x==0) {
            return(k/x);
        }
    }
}

//determines if the given number is prime.
//Returns 0 if not, 1 if so.
int prime(long int pr) {
    j=sqrt((double)pr);
    for(int i=2;i<=j;i++) {
        if(pr%i==0) {
            return 0;
        }
    }
    return 1;
}


void ce() {
    int k = 0;
    for(i=2;i<t;i++) {
        if(t % i == 0) {
            //nothing
        }
        else {
            flag=prime(i);
            if(flag==1&&i!=p&&i!=q) {
                e[k]=i;
                flag= cd(e[k]);

                if(flag>0) {
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


/**
 * The single-threaded RSA Operation; arbitrary precision with GMP
 */
void GMPmain(int numberOfTimes) {
	FILE* file;
	mpz_class e(EXP, KEY_BASE);
	mpz_class n(MOD, KEY_BASE);
	mpz_class p(FIRST_PRIME, KEY_BASE);
	mpz_class q(SECOND_PRIME, KEY_BASE);
	std::string mess = "12345678";
	mpz_class m(mess, KEY_BASE);

	// headers for the timing data
	file = fopen("/sdcard/RSA/GMPMainOutput.txt", "w");
	fprintf(file, "Time (micro)\t");
	fprintf(file, "Message\n");
	fclose(file);

	precompute(p, q, e, n);
	struct timeval start, end, diff;

	for(int timesCompleted = 0; timesCompleted < numberOfTimes; timesCompleted++) {
			gettimeofday(&start, NULL);
			GMPmod(m, e, n);
			gettimeofday(&end, NULL);

			fflush(stdout);
			fflush(stdin);

			timersub(&end, &start, &diff);
			file = fopen("/sdcard/RSA/GMPMainOutput.txt", "a");
			fprintf(file, "%ld\t", diff.tv_sec * 1000000 + diff.tv_usec);
			fprintf(file, "%s\n", mess.c_str());
			fclose(file);
		}

}


/**
 * Compute the bitsize
 */
void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n) {
	exp_bitsize = mpz_sizeinbase(exp.get_mpz_t(), 2);
	bin = bin_array(exp);
}


/**
 *
 */
int * bin_array(mpz_class num) {

	size_t size = exp_bitsize;
	int * bin = (int *)malloc(size * sizeof(int));
	int x = 0;
	mpz_class n = 1;
	mpz_class res;

	while(x < size) {
		res = n & num;
		res /= n;
		bin[x] = res.get_ui();
		x++;
		n *= 2;
	}
	return bin;
}

/**
 *
 */
mpz_class GMPmod(mpz_class &m, mpz_class &exp, mpz_class &n) {
	int x;
	mpz_class ret = 1;
	mpz_class val = m % n;
	for(x = 0; x < exp_bitsize; x++) {
		if(x) {
			val = (val * val) % n;
		}
		if(bin[x]) {
			ret *= val;
		}
	}

	ret %= n;

	return ret;
}


/**
 *
 */
void cMod(int c_base, int c_exponent, int c_den)
{
	unsigned int c_a = (c_base % c_den) * (c_base % c_den);
	unsigned long int c_ret = 1;
	float c_size = (float)c_exponent / 2;

	if(c_exponent == 0) {
		c_ret = c_base % c_den;
	}
	else {
		while(1) {
			if(c_size>0.5f) {
				c_ret=(c_ret*c_a)%c_den;
				c_size=c_size-1.0f;
			}
			else if(c_size==0.5f) {
				c_ret=(c_ret*(c_base%c_den))%c_den;
				break;
			}
			else break;
		}
	}
}


/**
 * Singlethreaded, limited precision rsa operation.
 * Calls cMod a given numberOfTimes and outputs timing data to a text file.
 */
void cMain(int numberOfTimes, int c_d, int c_n, int c_key) {
	uint64_t c_diff;
	struct timespec c_start, c_end;
	int completedTimes;
	FILE *file = fopen("sdcard/RSA/cMainOutput.txt", "w");
	fprintf(file, "Running RSA with C\n");
	for(completedTimes = 0; completedTimes < numberOfTimes; completedTimes++) {
	    clock_gettime(CLOCK_MONOTONIC, &c_start);
	    cMod(c_d, c_n, c_key);
	    clock_gettime(CLOCK_MONOTONIC, &c_end);
	    c_diff = BILLION * (c_end.tv_sec - c_start.tv_sec) + c_end.tv_nsec - c_start.tv_nsec;
	    fprintf(file, "Time taken: %llu\n", (long long unsigned int) c_diff);
	}
	fclose(file);
}



//Implementation of GetTickCount() for Linux systems.
//This code was originally written in Windows and this function is usually available in the
//windows.h include file
#include <sys/time.h>
long GetTickCount() {
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0) {
		return 0;
	}
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}



/**
 * Multithreaded rsa operation; incredibly inefficient
 * OpenCL, and only for regular data types (no GMP)
 */
void clMain(int numberOfTimes) {

    //declaring variables to be used for timing, usage of OpenCL, etc.
    char build_c[4096];
    //uint64_t diff;

    cl_int error;
    cl_platform_id platform;
    cl_device_id device;
    cl_uint platforms, devices;
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
    for ( i = 0; i < length; i++ ) {
        buf [i] = rand ( )%length1;
    }

    // Fetch the Platform and Device IDs; we only want one.
    error=clGetPlatformIDs(1, &platform, &platforms);
    if (error != CL_SUCCESS) {
            printf("\n Error number %d", error);
    }
    error=clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &devices);
    if (error != CL_SUCCESS) {
        printf("\n Error number %d", error);
    }

    //calculating e and d
    // We can modify this to allow for user input
    // it's hardcoded for now.

    //printf("\nENTER FIRST PRIME NUMBER\n");
    //scanf("%ld",&p);
    p = 59;
    flag=prime(p);
    if(flag==0) {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    //printf("\nENTER ANOTHER PRIME NUMBER\n");
    //scanf("%ld",&q);
    q = 83;
    flag=prime(q);
    if(flag==0||p==q) {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    //fflush(stdin);
    n=p*q;
    t=(p-1)*(q-1); // t = phi(n)

    ce();

    //printf("\nPOSSIBLE VALUES OF e AND d AND n ARE\n");
    for(i = 0; i < (j - 1); i++) {
        //printf("\n%ld\t%ld \t%d",e[i],d[i],(int)n);
        key = e[i];
        den = d[i];
    }

    // ENTER KEY VALUE
    //printf("\nEnter key parameter e from above set of values 1:");
    //scanf("%d",dev_key);
    //Should this be key parameter n from set of values 3,
    // or key parameter d from set of values 2?
    //Looks like parameter d makes more sense.
    //printf("\nEnter key parameter n from above set of values 2:");
    //scanf("%d",dev_den);


    // CREATE CONTEXT
    cl_context context=clCreateContext(0, 1, &device, NULL, NULL, &error);
    if (error != CL_SUCCESS) {
        printf("\n Error number %d", error);
    }

    //CREATE COMMAND QUEUE
    cl_command_queue cq = clCreateCommandQueue(context, device, 0, &error);
    if (error != CL_SUCCESS) {
        printf("\n Error number %d", error);
    }

    //CREATE FILE
    fflush(stdout);
    FILE *fil;
    fil = fopen("/sdcard/RSA/rsa.cl", "r");
    char *src;
    src = (char *)malloc(MAX_SOURCE_SIZE);
    srcsize=fread(src, 1, MAX_SOURCE_SIZE, fil);
    fclose(fil);
    const char *srcptr[]={src};

    // Submit the source code of the example kernel to OpenCL
    cl_program prog=clCreateProgramWithSource(context, 1, srcptr, &srcsize, &error);
    if (error != CL_SUCCESS) {
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


    struct timeval start, end, diff;


    int timesCompleted;
    fil = fopen("/sdcard/RSA/clMainOutput.txt", "w");
    fprintf(fil, "Elapsed time (microseconds\n");
    fclose(fil);
    for(timesCompleted = 0; timesCompleted < numberOfTimes; timesCompleted++) {
		gettimeofday(&start, NULL);/* mark start time */

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
		gettimeofday(&end, NULL);/* mark the end time */


		timersub(&end, &start, &diff);


		fil = fopen("/sdcard/RSA/clMainOutput.txt", "a");
		fprintf(fil, "%ld\n", diff.tv_sec * 1000000 + diff.tv_usec);
		fclose(fil);
    }
}

