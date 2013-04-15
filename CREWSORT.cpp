/*

Parallel Merge Sort - OpenMP
Computer Science and engineering, VI semeseter
National Institute of technology, Trichy

DESIGN AND ANALYSIS OF PARALLEL ALGORITHMS - Assignment
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <iostream>
#include <fstream>
using namespace std;

static int Comparator_function(const void *a, const void *b)
{
	return ( *( int*)a - *( int*)b );
}


void merge( int array1[],  int array2[],  int m,  int n) 
{
	 int i=0, j=0, k=0;
	 int size = m+n;
	 int *C = ( int *)malloc(size*sizeof( int));
	while (i < m && j < n) {
            if (array1[i] <= array2[j]) C[k] = array1[i++];
            else C[k] = array2[j++];
            k++;
	}
	if (i < m)
	{
		for ( int in = i; in < m; in++,k++) C[k] = array1[in];
	}
	else
	{
		for ( int in = j; in < n; in++,k++) C[k] = array2[in];
		}
	for( i=0; i<size; i++ ) array1[i] = C[i];
	free(C);
}


void CREW_MERGE( int *a,  int size,  int *tarr,  int N)
{
	 int i;
	while ( N>1 ) {
	    for( i=0; i<N; i++ )
		{
			tarr[i]=i*size/N;
			tarr[N]=size;
		}
		#pragma omp parallel for private(i) 
	    for( i=0; i<N; i+=2 ) {

		
		merge(a+tarr[i],a+tarr[i+1],tarr[i+1]-tarr[i],tarr[i+2]-tarr[i+1]);
		
	    }
	    N /= 2;
	}
}

void print( int *arr,  int size)
{
	fstream print_par;
	print_par.open("output_serial.txt");
	for( int i = 0; i < size; i++)
	{
		cout<<" "<<arr[i];
	}
	print_par.close();
}

int main(int argc,char *argv[])
{
	
	 int i;
	 int size;
	cout<<"\n Crew sort implementation";
	cout<<"\n Enter the number of elements to be sorted :";
	cin>>size;
	 int *a = ( int *)malloc(size*sizeof( int));
	
	for(i=0; i<size; i++)
	{
		a[i] = (rand()%32767)%10000;
	}

	int threads = omp_get_max_threads();
	omp_set_num_threads(threads);
	 int *tarr = ( int *)malloc((threads+1)*sizeof( int));
	for(i=0; i<threads; i++)
	{
		tarr[i]=i*size/threads; 
		tarr[threads]=size;
	}
	double start = omp_get_wtime();
	#pragma omp parallel for private(i)
	for(i=0; i<threads; i++)
	{
		
			
		qsort(a+tarr[i],tarr[i+1]-tarr[i],sizeof(int),Comparator_function);
	}
	double middle = omp_get_wtime();

	if( threads>1 )
	{
		CREW_MERGE(a,size,tarr,threads);
	}
	double end = omp_get_wtime();
	cout<<"\n CREW-SORT Time is : "<<end-start<<"\n Merge time is : "<<end-middle;
	cout<<"\n Total no of threads used : "<<threads;
	print(a, size);
	for( int i=1; i<size; i++){
		if( a[i-1]>a[i] )
		{
			cout<<"\n Elements at position "<<i<<" and "<<i-1<<" are not sorted. ";
		}
	}
	cout<<"\n";
	system("pause");
	return 0;
}
