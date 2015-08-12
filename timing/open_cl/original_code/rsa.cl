__kernel void mod(int base,int exponent,int den, int ret)
{
	unsigned int a=(base%den)*(base%den);
//	unsigned long int ret=1;
	float size=(float)exponent/2;
	if(exponent==0)
	{
		ret=base%den;
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
			ret=(ret*(base%den))%den;
			break;
			}
			else
			{
				break;
			}
		}
   
	}
}
 


__kernel void RSA( __global const int * num,__global int *key,__global int *den,__global int * result)
{
 int i = get_global_id(0);   //current thread
 int n = get_global_size(0); //input size
 int iData = num[i];
 unsigned long int r=1;
 unsigned long int *ret=&r;
 //int temp;
 if(i<32*128)               // no. of elements to process
 {   
	mod(num[i],*key,*den,*ret);
	
	result[i] =*ret;
 }
}
