#include "include/binheap.h"
#include "include/total_orders.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define MAX_SIZE 16

void int_printer(const void *value)
{
  printf("%d", *((const int *)value));
}


int main(){

	int *B=(int *)malloc(sizeof(int)*MAX_SIZE);
  	
  	B[0] = 4;
  	B[1] = 3;
  	B[2] = 2;
  	B[3] = 7;
  	
  	int *A=(int *)malloc(sizeof(int)*MAX_SIZE);
  	A[0] = 10;
  	A[1] = 5;
  	A[2] = 8;
  	A[3] = 12;
  	A[4] = 1;

	
  	 
	binheap_type *minH= build_heap(B,4,MAX_SIZE,sizeof(int),leq_int);
	
	print_heap(minH, int_printer);
	
	for(int i=0; i<5; i++){
		insert_value(minH, A+i);
	}
	
	print_heap(minH, int_printer);
	

	
	
	
	delete_heap(minH);
	free(B); 	

 	return 0;
}
