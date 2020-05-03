#include "quick_sort.h"
#define ADDR(A, i, key_size) (A+(i)*(key_size))

void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order leq)
{
    quick_sort_aux(A, 0, n, elem_size, leq);  
}

void quick_sort_aux(void *A, unsigned int l, unsigned int r, const size_t elem_size, total_order leq)
{
	while(l<r){
		unsigned int p = partition(A, l, r-1, l, elem_size, leq);
		
		quick_sort_aux(A, l, p, elem_size, leq);
		l = p+1;	
	}
}

unsigned int partition(void *A, unsigned int i, unsigned int j, unsigned int p, const size_t elem_size, total_order leq)
{	
	swap( ADDR(A,i,elem_size), ADDR(A,p,elem_size), elem_size );
	p = i;
	i++;
	
	while(i<=j)
	{
		if( !leq(ADDR(A,i,elem_size), ADDR(A,p,elem_size)) )
		{
			swap( ADDR(A,i,elem_size), ADDR(A,j,elem_size), elem_size );
			j--;
		}
		else 
		{
			i++;
		}
	}
	
	swap( ADDR(A,p,elem_size), ADDR(A,j,elem_size), elem_size );

	return j;
}
