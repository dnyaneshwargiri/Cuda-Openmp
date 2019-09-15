#include<stdio.h>
#include<math.h>
#define SIZE 1024
__global__ void max(int * A, int * C)
{
        int i=blockIdx.x*blockDim.x+threadIdx.x;
        A[2*i] < A[2*i+1]?C[i]=A[2*i]:C[i]=A[2*i+1];

}
int main()
{
        int A[SIZE];
        int *devA,*devC;
        for(int j=0;j<SIZE;j++)
        {
                A[j]=SIZE-j;
        }
        cudaMalloc((void **)&devA,SIZE*sizeof(int));
        cudaMalloc((void **)&devC,SIZE*sizeof(int));
        for(int j=1;j<log2((double)SIZE);j++)
        {
                cudaMemcpy(devA,A,SIZE*sizeof(int),cudaMemcpyHostToDevice);
                max<<<1,SIZE/pow(2,j)>>>(devA,devC);
                cudaMemcpy(&A,devC,SIZE*sizeof(int),cudaMemcpyDeviceToHost);
        }
        A[0] < A[1]?printf("Min is:%d",A[0]) : printf("Min is:%d",A[1]);
        cudaFree(devA);
        cudaFree(devC);
        return 0;

}
