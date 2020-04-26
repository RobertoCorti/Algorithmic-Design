#include <binheap.h>
#include <string.h>
#include <stdio.h>

//key operations pre-defined as macros

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*(node)+1)
#define RIGHT_CHILD(node) (2*(node+1))

#define VALID_NODE(H, node) ((H)->num_of_elem > (node))
#define ADDR(H, node) ((H)->A+(node)*(H->key_size))
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

	//the minimum is stored in the root aka A[0]
    return ADDR(H, 0);
}


void swap_keys(binheap_type *H, unsigned int n_a, unsigned int n_b)
{
	void *p_a = ADDR(H, n_a);
	void *p_b = ADDR(H, n_b);
	void *tmp = malloc(H->key_size);
	
	memcpy(tmp, p_a, H->key_size);
	memcpy(p_a, p_b, H->key_size);
	memcpy(p_b, tmp, H->key_size);
	
	free(tmp);
} 

//given node, it gives the index i* of key_pos s.t. key_pos[i*]=node
unsigned int search(binheap_type *H, unsigned int node){

	for(unsigned int k=0; k<H->num_of_elem; k++){
		if(H->key_pos[k] == node){
			return k;
		}
	}
	
	return 999;
}


void heapify(binheap_type *H, unsigned int node){

	unsigned int n = search(H, node);
	unsigned int dst_node=n; //in the slides m <- i
	unsigned int j;
	
	j = search(H,2*(node)+1);
	
	if (j != 999){ 
	
		if(VALID_NODE(H, j) && H->leq( ADDR(H, H->key_pos[j]), ADDR(H, H->key_pos[dst_node]) ) ) { 
			dst_node=j;
		}
	}
	
	j = search(H, 2*(node+1));
	
	if (j != 999){
	 
		if(VALID_NODE(H, j) && H->leq( ADDR(H, H->key_pos[j]) , ADDR(H, H->key_pos[dst_node])) ) { 
		dst_node=j;
		}
	}
	
	if (dst_node != n){
		unsigned int c = dst_node;
		H->key_pos[dst_node] = H->key_pos[n];
		H->key_pos[n] = c;
		
		heapify(H, H->key_pos[n]);		
	}
}

const void *extract_min(binheap_type *H)
{
  if(is_heap_empty(H)){
		return NULL;
  }

	//swapping keys among the root
	//and the right-most leaf of last level
	swap_keys(H, 0, H->num_of_elem-1);	
	
	//deleting the right most leaf of the last level
	H->num_of_elem--;
	
	heapify(H, 0);

  return ADDR(H, H->num_of_elem+1);
}

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

const void *decrease_key(binheap_type *H, void *node, const void *value)
{
    unsigned int node_idx = INDEX_OF(H, node);
    
    //if node not belong to H or *value->*node return NULL
    if(VALID_NODE(H,node) || !(H->leq(value,node)) ) {
    	return NULL;
    }
    
    memcpy(node, value, H->key_size);

	unsigned int parent_idx = PARENT(node_idx);
	void *parent = ADDR(H, parent_idx);
	
	while((node_idx != 0) && (!H->leq(parent,node)) ){
		node = parent;
		node_idx = parent_idx;
		
		parent_idx = PARENT(node_idx);
		parent = ADDR(H, node_idx);
	} 
	
    return node;
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
    
    void * new_node_addr = ADDR(H, H->num_of_elem);
    
    memcpy(new_node_addr, H->max_order_value, H->key_size);
    
    H->num_of_elem++;

    return decrease_key(H, new_node_addr, value);
}

void print_heap(binheap_type *H, 
                void (*key_printer)(const void *value))
{
	unsigned int node = 0;						  
    unsigned int index = search(H,node);
    printf("search(h, %d) = %d \n",node,  index);
    unsigned int next_level_node = 1; //store the index of the left-most node of the next level    								 
    unsigned int next_level_node_idx = search(H,next_level_node);
    printf("search(h, %d) = %d \n",next_level_node,  next_level_node_idx);
    
    for (unsigned int k=0; k<H->num_of_elem; k++){
    	printf(" %d \t", H->key_pos[k]);
    }
    printf("\n");
 
    while(node < H->num_of_elem){
    
    	if(index == next_level_node_idx){
    		printf("\n");
    		next_level_node=LEFT_CHILD(node);
    		next_level_node_idx = search(H,next_level_node);
    	}
    	else 
    	{
    		printf("\t");
    	}
    	
    	key_printer(ADDR(H,(int)index));
    	
    	node++;
    	index = search(H,node);
    }
    
    printf("\n");
}










