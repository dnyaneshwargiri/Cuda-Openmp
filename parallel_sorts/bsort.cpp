#include<iostream>
#include<math.h>
#include<cstdlib>
#include<stdlib.h>
#include<omp.h>

using namespace std;


void bsort(int a[],int i,int j)
{  int temp;
	omp_set_num_threads(5);
	
	for(int m=i;m<j;m++)
	{ 
	  #pragma omp parallel  for
	  for(int n=m;n<=j;n++)
	   {
		if (a[n] < a[m] )
		{
		temp=a[m];
		a[m]=a[n];
		a[n]=temp;
		} 
	   }
	}

}


void bsort2(int a[],int i,int j)
{
	int temp;
	for(int m=i;m<j;m++)
	{
	  for(int n=m;n<=j;n++)
	   {
		if (a[n] < a[m] )
		{
		temp=a[m];
		a[m]=a[n];
		a[n]=temp;
		} 
	   }
	}
}




int main()
{
	int a[10];
	
	for (int i=0;i<10;i++)
	{
		a[i]=rand() % 12;
	}
	double s,e;
	s=omp_get_wtime();
	bsort(a,0,9);
	e=omp_get_wtime();
	for(int i=0;i<10;i++)
    {
        cout<<"\n"<<a[i];
    }
    cout<<"\n Time "<<(e-s);
	
	for (int i=0;i<10;i++)
	{
		a[i]=rand() % 12;
	}
	s=omp_get_wtime();
	bsort2(a,0,9);
	e=omp_get_wtime();
	for(int i=0;i<10;i++)
    {
        cout<<"\n"<<a[i];
    }
	cout<<"\n Time "<<(e-s);
}
