#include<iostream>
#include<time.h>
#include<omp.h>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	long int i,n=109396;
	long int a[n];
	double start=0, end=0;
    
    //a= new int[n];
	for(i=0;i<n;i++)
	{
		a[i]= i;
	}	
	long sum=0;
	cout<<"\nSerial ";
start=omp_get_wtime();
for(int i=0;i<n;i++)
    {
	sum +=a[i];  
	}
	 end=omp_get_wtime();
   cout<<"\nSum Is "<<sum<<"(should be "<< n*(n-1)/2<<")";
   cout<<"\nTime is :"<<end-start;
cout<<"\nParallel ";
    start=omp_get_wtime();
   sum=0;
   omp_set_num_threads(16);
   #pragma omp /*parallel */ nowait for  reduction(+:sum) 
   for(int i=0;i<n;i++)
    {
	sum +=a[i];  
	}
	 end=omp_get_wtime();
   cout<<"\nSum Is "<<sum<<"(should be "<< n*(n-1)/2<<")";
   cout<<"\nTime is :"<<end-start;
   long max=a[0];
   #pragma omp parallel nowait for  shared( max) 
   for(int i=0;i<n;i++)
   {
	   if(max < a[i])
	  { max=a[i]; }
   }
   
   
    cout<<"\nMAx Is "<<max;
   
    
    
return 0;
}
