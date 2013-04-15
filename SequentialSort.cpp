/*

Parallel Merge Sort - OpenMP
Computer Science and engineering, VI semeseter
National Institute of technology, Trichy

DESIGN AND ANALYSIS OF PARALLEL ALGORITHMS - Assignment
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#define ZERO 0
using namespace std;

int partition( int *A, int l, int u)
{
	 int p=l,q=u+1;
	 int i=A[l],t;
	while(q>=p)
	{
		while(A[++p]<i);
		while(A[--q]>i);
		if(q>p)
		{
			t=A[p];
			A[p]=A[q];
			A[q]=t;
		}
	}
	t=A[l];
	A[l]=A[q];
	A[q]=t;
	return q;
}
void SequentialQuicksort( int *A, int l, int u)
{
	 int i;
	if(u>l)
	{
		i=partition(A,l,u);
		SequentialQuicksort(&(*A),l,i-1);
		SequentialQuicksort(&(*A),i+1,u);
	}
}

void print( int *arr,  int size)
{
	fstream print_seq;
	print_seq.open("serial.txt");
	for( int i = 0; i < size; i++)
	{
		print_seq<<" "<<arr[i];
	}
	print_seq.close();
}
int main(int argc,char *argv[])
{
	 int i;
	 int size;
	 double start,end;
	cout<<"\n Crew sort implementation- 106110005, 106110014, 106110093\n";
	cout<<"\n Enter the number of elements to be sorted :";
	cin>>size;
	 int *a = ( int *)malloc(size*sizeof( int));
	
	for(i=0; i<size; i++)
	{
		a[i] = (rand()%32767)%10000;
	}
	start = omp_get_wtime();
	
	SequentialQuicksort(a, 0, size);

	
	
	print(a, size);
	end = omp_get_wtime();
    cout<<"\n EREW-SORT Time is : "<<end-start;

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
