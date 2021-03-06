#include "quick_sort.h"
#include "swap.h"
#define ADDR(A, i, key_size) (A+(i)*(key_size))

pair_type tri_partition(void *A, unsigned int pivot, unsigned int left, unsigned int right,const size_t elem_size, total_order leq)
{
    pair_type pair;
    swap(ADDR(A,pivot,elem_size),ADDR(A,left,elem_size),elem_size);
    pivot=left;
    unsigned int i = left+1;
    unsigned int j = right;
    unsigned int same=0;
 	int equal;
    while(i<=j)
    {
        equal = leq(ADDR(A,i,elem_size),ADDR(A,pivot,elem_size)) && leq(ADDR(A,pivot,elem_size),ADDR(A,i,elem_size)) ;
        
        //A[i] != A[pivot]
        if(!equal)
        {     
        	//A[i] > A[pivot]   
        	if( leq(ADDR(A,pivot,elem_size),ADDR(A,i,elem_size)) )
        	{ 
           	  swap(ADDR(A,i,elem_size),
           	       ADDR(A,j,elem_size),
           	       elem_size);
                j--;
            }
            
            //A[i] < A[pivot] 
            else
            { 
            
            	swap(ADDR(A,i,elem_size),
           	       ADDR(A,pivot-same,elem_size),
           	       elem_size);
                pivot=i;
                i++;
            }
        }
   
   		//A[i] = A[pivot]     
        else
        {
            pivot=i;
            i++;
            same++;
        }
        
    }
      
    swap(ADDR(A,pivot,elem_size),ADDR(A,j,elem_size),elem_size);  
    
    pair.second=j;
    pair.first=j-same;
    return pair;
}


void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order leq)
{
    quick_sort_aux(A, 0, n, elem_size, leq);  
}

void quick_sort_aux(void *A, unsigned int l, unsigned int r, const size_t elem_size, total_order leq)
{
	while(l<r){
		unsigned int p = partition(A, l, r, l, elem_size, leq);
		
		quick_sort_aux(A, l, p, elem_size, leq);
		l = p+1;	
	}
}

unsigned int partition(void *A, unsigned int l, unsigned int r, unsigned int pivot, const size_t elem_size, total_order leq)
{	
	swap( ADDR(A,l,elem_size), ADDR(A,pivot,elem_size), elem_size );
	pivot = l;
	unsigned int i = l + 1;
	unsigned int j = r - 1;
	
	while(i<=j)
	{
		if( !leq(ADDR(A,i,elem_size), ADDR(A,pivot,elem_size)) )
		{
			swap( ADDR(A,i,elem_size), ADDR(A,j,elem_size), elem_size );
			j--;
		}
		else 
		{
			i++;
		}
	}
	
	swap( ADDR(A,pivot,elem_size), ADDR(A,j,elem_size), elem_size );

	return j;
}


unsigned int balanced_partition(void *A, unsigned int l, unsigned int r, unsigned int pivot, const size_t elem_size, total_order leq)
{	
	swap( ADDR(A,l,elem_size), ADDR(A,pivot,elem_size), elem_size );
	pivot = l;
	unsigned int i = l + 1;
	unsigned int j = r - 1;
	int side = 1;
	
	while(i<=j)
	{
		int equal = leq ( ADDR(A,i,elem_size), ADDR(A,pivot,elem_size) ) && leq( ADDR(A,pivot,elem_size), ADDR(A,i,elem_size) );
	
		if ( equal ){
			side = !side;
        }
	
		if( !(leq( ADDR(A,i,elem_size), ADDR(A,pivot,elem_size)))  ||  (equal && !side) )
		{
			swap( ADDR(A,i,elem_size), ADDR(A,j,elem_size), elem_size );
			j--;
		}
		else 
		{
			i++;
		}
	}
	
	swap( ADDR(A,l,elem_size), ADDR(A,j,elem_size), elem_size );
	
	return j;
}
