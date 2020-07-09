#include "binheap.h"
#include "total_orders.h"
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
  	 
	binheap_type *minH= build_heap(B,4,MAX_SIZE,sizeof(int),leq_int);
	
	printf("\n  BINARY HEAP\n");
	printf("\n");
	print_heap(minH, int_printer);


	printf("\nCall insert value = ");
	B[4] = 20;
	printf("%d \n\n", B[4]);
	insert_value(minH, &B[4]);
	print_heap(minH, int_printer);

	const int * min = extract_min(minH);
	
	printf("\nCall extract_min, I extracted %d \n", *(min) );
	printf("\n");
	print_heap(minH, int_printer);
	
	printf("\nCall is_heap_empty: (0: False, 1: True) ");
	printf("%d \n", is_heap_empty(minH));


	printf("\nCall min_value, which is ");
	int s = *( (int*) min_value(minH) );
	printf("%d \n", s );



	free(B); 
 	return 0;
}
