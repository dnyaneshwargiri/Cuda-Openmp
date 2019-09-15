#include<iostream>
#include<time.h>
#include<omp.h>
#include<cstdlib>
#include<ctime>
using namespace std;


void mergesort(long int a[],long int i,long int j);
void merge(long int a[],long int i1,long int j1,long int i2,long int j2);

void mergesort(long int a[],long int i,long int j)
{
    int mid;
    if(i<j)
    {
        mid=(i+j)/2;
        
        #pragma omp parallel sections 
        {

            #pragma omp section
            {
                mergesort(a,i,mid);        
            }

            #pragma omp section
            {
                mergesort(a,mid+1,j);    
            }
        }

        merge(a,i,mid,mid+1,j);    
    }

}
 
void merge(long int a[],long int i1,long int j1,long int i2,long int j2)
{
    int temp[1000];    
    int i,j,k;
    i=i1;    
    j=i2;    
    k=0;
    
    while(i<=j1 && j<=j2)    
    {
        if(a[i]<a[j])
        {
            temp[k++]=a[i++];
        }
        else
        {
            temp[k++]=a[j++];
	    }    
    }
    
    while(i<=j1)    
    {
        temp[k++]=a[i++];
    }
        
    while(j<=j2)    
    {
        temp[k++]=a[j++];
    }
        
    for(i=i1,j=0;i<=j2;i++,j++)
    {
        a[i]=temp[j];
    }    
}


int main()
{
     long int i,n=1000;
	long int a[n];
	double wcpt,start1=0, end1=0;
    
    //a= new int[n];
	for(i=0;i<n;i++)
	{
		a[i]= rand() % 16;
	}	

    start1=omp_get_wtime();
    mergesort(a, 0, n-1);
    end1=omp_get_wtime();
    
    wcpt = end1 - start1;
    
    
		
	//cout<<"\n\nEfficiency is : "<<wcst/wcpt<<"\n";
    
    cout<<"\n sorted array is=>";
    for(i=0;i<n;i++)
    {
        cout<<"\n"<<a[i];
    }
    
    cout<<"\n\nExe time for parallel:"<<wcpt;
       
    return 0;
    
}


