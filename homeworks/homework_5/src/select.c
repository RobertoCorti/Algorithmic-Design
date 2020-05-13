#include "select.h"
#include "swap.h"
#include "quick_sort.h"


#define ADDR(A, i, key_size) (A+(i)*(key_size))

unsigned int select_aux(void *A, unsigned int i, unsigned int l, unsigned int r, const size_t elem_size, total_order leq);
  
unsigned int select_pivot(void* A, unsigned int n, const size_t elem_size, total_order leq);
 
void quicksort_select_aux(void *A, unsigned int left,unsigned int right,const size_t elem_size,total_order leq);

unsigned int select_index(void *A, const unsigned int n, 
                          const unsigned int i,
                          const size_t elem_size, 
                          total_order leq)
{	
	
	return select_aux(A, i, 0, n, elem_size, leq);	
}

unsigned int select_aux(void *A, unsigned int i, unsigned int l, unsigned int r, const size_t elem_size, total_order leq)
{

	if(r-l<=10){
		quick_sort(A, r-l, elem_size, leq);
		return i;		
	}
	
	unsigned int j = select_pivot(ADDR(A, l, elem_size), r-l, elem_size, leq);
	unsigned int k = balanced_partition(A, l, r, j, elem_size, leq);
	
	if(i==k){
		return k;
	}
	
	if(i<k){
		return select_aux(A, i, l, k-1, elem_size, leq); 
	}
	
	else {
		return select_aux(A, i, k+1, r, elem_size, leq);
	}

}


unsigned int select_pivot(void* A, unsigned int n, const size_t elem_size, total_order leq)
{
	if(n<=10){
		quick_sort(A, n, elem_size, leq);
		return (n)/2;		
	}
	
	unsigned int chunks = n / 5 ;
	unsigned int c_l, c_r;
	
	for(unsigned int c=0; c<chunks; c++){
		c_l = c*5;
		c_r = 5 + c*5;
		quick_sort(ADDR(A, c_l, elem_size), 5, elem_size, leq);
        swap(ADDR(A, c_l+2, elem_size),ADDR(A, c, elem_size),elem_size);
	}
	
	return select_index(A,chunks,chunks/2,elem_size,leq);

}

void quicksort_select_aux(void *A, unsigned int left,unsigned int right,const size_t elem_size,total_order leq){

	unsigned int p, pivot;
	
    while(left<right){
      	//p = select_pivot(ADDR(A, left, elem_size), right-left, elem_size, leq);
		pivot = balanced_partition(A, left, right, left, elem_size, leq);
		
		quicksort_select_aux(A, left, pivot, elem_size, leq);
		left = pivot+1;	
	}
    
}

void quick_sort_select(void *A, const unsigned int n, 
                       const size_t elem_size, 
                       total_order leq)
{
	quicksort_select_aux(A,0,n,elem_size,leq);
	
}
