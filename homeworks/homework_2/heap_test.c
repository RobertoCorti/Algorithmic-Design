#include "include/binheap.h"
#include "include/total_orders.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 15

void int_printer(const void *value)
{
  printf("%d", *((const int *)value));
}


int main(){

	int *B=(int *)malloc(sizeof(int)*MAX_SIZE);
  	
  	for(int k=0; k<MAX_SIZE; k++){
  		B[k] = (rand() % (MAX_SIZE + 1)); 
  	}

	printf("Call build_heap\n");
	binheap_type *minH= build_heap(B,MAX_SIZE-2,MAX_SIZE,sizeof(int),leq_int);
	print_heap(minH, int_printer);
	
	printf("Call heapify on %d \n", B[MAX_SIZE/2]);
	heapify(minH, B[0]);
	print_heap(minH, int_printer);
	
	printf("Call is_heap_empty  (False=0) (True=1) \n");
	printf("Output: %d \n", is_heap_empty(minH));
	
	printf("Call min_value: \n");
	int s = *( (int*) min_value(minH) );
	printf("Output: %d \n", s );
	
	
	printf("Call insert value = 0\n");
	int i=0;
	insert_value(minH, &i);
	print_heap(minH, int_printer);	

	printf("Call delete_heap\n");
	delete_heap(minH);

	return 0;
}
