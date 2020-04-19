#include "include/binheap.h"
#include "include/total_orders.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define MAX_SIZE 10000

void int_printer(const void *value)
{
  printf("%d", *((const int *)value));
}


int main(){

	struct timespec i_time0, i_time1;
	FILE * fp;

	int *B=(int *)malloc(sizeof(int)*MAX_SIZE);
  	
  	for(int k=0; k<MAX_SIZE; k++){
  		B[k] = (rand() % (MAX_SIZE + 1)); 
  	}
  	
	int *A=(int *)malloc(sizeof(int)*MAX_SIZE);
	
	fp = fopen ("insertion_time.txt","w");
	fprintf (fp, "N \t time \n");
	for(int n=5;n<MAX_SIZE;n+=10)
	{
		fprintf (fp, "%d \t", n);
		binheap_type *minH= build_heap(A,0,n,sizeof(int),leq_int);
		clock_gettime(CLOCK_REALTIME, &i_time0);
		for(int i = 0; i<n; i++)
		{
			insert_value(minH, &B[i]);
		}
		clock_gettime(CLOCK_REALTIME, &i_time1);
    	fprintf(fp, "%lf \n", (i_time1.tv_sec-i_time0.tv_sec) + (i_time1.tv_nsec-i_time0.tv_nsec)/1E9);
    	
    	delete_heap(minH);
	}

 	free(A);
	free(B); 	

 	return 0;
}
