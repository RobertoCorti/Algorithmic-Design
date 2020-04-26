#include "include/binheap.h"
#include "include/total_orders.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define MAX_SIZE 7

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
  	
  	int i = 1;
  	int *p = &i; 
  	
	binheap_type *minH= build_heap(B,4,MAX_SIZE,sizeof(int),leq_int);
	
	print_heap(minH, int_printer);
	
	insert_value(minH, p);
	
	print_heap(minH, int_printer);
	
	delete_heap(minH);
	free(B); 	

 	return 0;
}
