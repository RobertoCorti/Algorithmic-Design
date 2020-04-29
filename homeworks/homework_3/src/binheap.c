#include <binheap.h>
#include <string.h>
#include <stdio.h>

//key operations pre-defined as macros

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*(node)+1)
#define RIGHT_CHILD(node) (2*(node+1))

#define VALID_NODE(H, node) ((H)->num_of_elem > (node))
#define ADDR(H,node) ((H)->A+((H)->key_pos[node])*(H)->key_size)
#define INDEX_OF(H, addr) ((addr-(H->A))/(H->key_size))


int is_heap_empty(const binheap_type *H)
{
    return (H->num_of_elem == 0);
}

const void *min_value(const binheap_type *H)
{
    if(is_heap_empty(H)){
    	return NULL;
    }
    
    return ADDR(H, 0);
}

void swap_keys(binheap_type *H, unsigned int index_a, unsigned int index_b){

	unsigned int tmp = H->key_pos[index_a];
	H->key_pos[index_a] = H->key_pos[index_b];
	H->key_pos[index_b] = tmp;

}


void heapify(binheap_type *H, unsigned int node){

	unsigned int dst_node = node;
	unsigned int child;
	
	child = RIGHT_CHILD(node);
		
	if(VALID_NODE(H, child) && H->leq( ADDR(H, child), ADDR(H, dst_node) ) ) { 
			dst_node = child;
	}
	
	child = LEFT_CHILD(node);
	
	if(VALID_NODE(H, child) && H->leq( ADDR(H, child), ADDR(H, dst_node) )) { 
		dst_node = child;
	}
	
	if (dst_node != node){
		swap_keys(H, dst_node, node);
		heapify(H, node);		
	}
}
/*
const void *extract_min(binheap_type *H)
{

	
  	if(is_heap_empty(H)){
		return NULL;
  	}
	//swapping keys among the root
	//and the right-most leaf of last level
	unsigned int root = search(H,0);
	printf("search(H,0) = %d \n", root);
	unsigned int last = search(H, H->num_of_elem-1);
	printf("search(H,H->num_of_elem-1) = %d \n", last);
	unsigned int c = H->key_pos[last];
	H->key_pos[last] = H->key_pos[root];
	H->key_pos[root] = c;	
	
	for (unsigned int k=0; k<H->num_of_elem; k++) {
		printf("%d \t", H->key_pos[k]);
	}
	printf("\n");
	
	//deleting the right most leaf of the last level
	H->num_of_elem--;
	
	heapify(H, 0);
	
  return ADDR(H, root);
}
*/
const void * find_the_max(void *A, const unsigned int num_of_elem,
						  const unsigned int key_size,total_order_type leq)
{
	if(num_of_elem==0){
		return NULL;
	}						  
	
	const void *max_value = A;
	for(const void *addr=A+key_size;
	    addr!=A+num_of_elem*key_size; addr+=key_size)
	{
	 	if(!leq (addr, max_value))  { max_value = addr;}
	}	
	
	return max_value;				  
}

binheap_type *build_heap(void *A, 
                         const unsigned int num_of_elem,
                         const unsigned int max_size,  
                         const size_t key_size, 
                         total_order_type leq)
{
	//ction of H
    binheap_type *H = (binheap_type *)malloc(sizeof(binheap_type)); 
    H->A = A;
    H->num_of_elem = num_of_elem;
    H->max_size = max_size;
    H->key_size = key_size;
    H->leq = leq;
    H->max_order_value = malloc(key_size);

	if (num_of_elem == 0) {
		return H;
	}
	//get max among A[:num_of_elem-1] and store in its max_value
	const void *value = find_the_max(A,num_of_elem, key_size,leq);
	memcpy(H->max_order_value, value, key_size);
	
	H->key_pos = (unsigned int *)malloc(sizeof(unsigned int)*max_size);
	
	for(unsigned int i=0; i<num_of_elem; i++){
		H->key_pos[i] = i;
	}

	for(unsigned int i=num_of_elem/2; i>0; i--)
	{
		heapify(H,i);
	}						 
	heapify(H,0);
	
    return H;
}

void delete_heap(binheap_type *H)
{
	//dtor of heap, so I have to free its "dynamical" members
    free(H->max_order_value);
    free(H);
}

const void *decrease_key(binheap_type *H, unsigned int n, const void *value)
{ 
	unsigned int node = n;
    void * node_addr = ADDR(H, node);
    
    //if node not belong to H or *value->*node return NULL
    if(!VALID_NODE(H,node) || !(H->leq(value, node_addr)) ) {
    	return NULL;
    }
    
    memcpy(node_addr, value, H->key_size);
       
	unsigned int parent = PARENT(node);

	while((node != 0) && (!H->leq(ADDR(H, PARENT(node)) ,node_addr)) ){
		
		parent = PARENT(node);
		swap_keys(H, parent, node);
		
		node = parent;
		node_addr = ADDR(H, node);
	} 
	
    return ADDR(H,node);
}

const void *insert_value(binheap_type *H, const void *value)
{

    if (H->max_size == H->num_of_elem){
    	return NULL;
    }
    
    if(H->num_of_elem == 0 || (H->leq(H->max_order_value, value)) ) 
    {
    	memcpy(H->max_order_value, value, H->key_size);
    }
    
    H->key_pos[H->num_of_elem] = H->num_of_elem;
    
    void * new_node_addr = ADDR(H, H->num_of_elem);
    
    memcpy(new_node_addr, H->max_order_value, H->key_size);
    
    H->num_of_elem++;

    return decrease_key(H, H->num_of_elem-1, value);
}

void print_heap(binheap_type *H, 
                void (*key_printer)(const void *value))
{
	unsigned int node = 0;						  
    unsigned int next_level_node = 1; //store the index of the left-most node of the next level    								 
 
 
    while(node < H->num_of_elem){
    
    	if(node == next_level_node)
    	{
    		printf("\n");
    		next_level_node=LEFT_CHILD(node);
    	}
    	
    	else 
    	{
    		printf("\t");
    	}
    	
    	key_printer( ADDR(H, node) );
    	
    	node++;
    }
    
    printf("\n");
}










