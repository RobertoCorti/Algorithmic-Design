#include <binheap.h>
#include <string.h>
#include <stdio.h>


//key operations pre-defined as macros

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*(node)+1)
#define RIGHT_CHILD(node) (2*(node+1))
#define VALID_NODE(H, node) ((H)->num_of_elem>(node))
#define ADDR(H, node) ((H)->A+(node)*(H)->key_size)
#define INDEX_OF(H, addr) ((addr-((H)->A))/((H)->key_size))

#define KEY_ADDR(H, index) (&(H->key_pos[index]))
#define REV_ADDR(H, index) (&(H->rev_pos[index]))


int is_heap_empty(const binheap_type *H)
{
    return (H->num_of_elem == 0);
}

const void *min_value(const binheap_type *H)
{
    if(is_heap_empty(H)){
    	return NULL;
    }
    
    return ADDR(H, *(H->key_pos));
}


void swap_keys(binheap_type *H, unsigned int pos_index_a, unsigned int pos_index_b){

	unsigned int* id_a = KEY_ADDR(H, pos_index_a);
	unsigned int* id_b = KEY_ADDR(H, pos_index_b);
	unsigned int* id_tmp = malloc(sizeof(unsigned int));

	memcpy(id_tmp, id_a, sizeof(unsigned int));
	memcpy(id_a, id_b, sizeof(unsigned int));
	memcpy(id_b, id_tmp, sizeof(unsigned int));

	free(id_tmp);

	//update rev_pos
	for(int i=0; i<(H)->num_of_elem; i++) 
  	{
    	unsigned int index = H->key_pos[i]; 
    	H->rev_pos[index] = i;
  	}
}


void heapify(binheap_type *H, unsigned int node){

	unsigned int dst_node = node;
	unsigned int child;
	unsigned int addr_node;
	unsigned int addr_dst_node;
	unsigned int addr_child;
		
	do {
        node = dst_node;
		addr_node = *(KEY_ADDR(H, node));

        child = RIGHT_CHILD(node);
		addr_child = *(KEY_ADDR(H, child));

		addr_dst_node = *(KEY_ADDR(H, dst_node));

        if(VALID_NODE(H, child) && H->leq( ADDR(H, addr_child), ADDR(H, addr_dst_node) ) ) { 
			dst_node = child;
			addr_dst_node = *(KEY_ADDR(H, dst_node));
	    }
	
	    child = LEFT_CHILD(node);
		addr_child = *(KEY_ADDR(H, child));

	    if(VALID_NODE(H, child) && H->leq( ADDR(H, addr_child), ADDR(H, addr_dst_node) )) { 
	    	dst_node = child;
	    }
    
	    if (dst_node != node){
	    	swap_keys(H, dst_node, node);		
	    }
        
    } while(dst_node != node);

}

const void *extract_min(binheap_type *H)
{
	
  	if(is_heap_empty(H)){
		return NULL;
  	}
	//swapping keys among the root
	//and the right-most leaf of last level
	swap_keys(H, 0, (H->num_of_elem)-1);
    unsigned int id_min = *(KEY_ADDR(H, (H->num_of_elem)-1));
    
	
	// deleting the right most leaf 

	if (H->num_of_elem>1)
	{
		H->num_of_elem--;
		heapify(H,0);
	}
	else
	{
		H->num_of_elem--;
	}
    
    return ADDR(H, id_min);
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

	H->key_pos = (unsigned int *)malloc(sizeof(unsigned int)*max_size);
	H->rev_pos = (unsigned int *)malloc(sizeof(unsigned int)*max_size);

	for(unsigned int i=0; i<num_of_elem; i++){
		H->key_pos[i] = i;
	}

	if (num_of_elem == 0) {
		return H;
	}
	//get max among A[:num_of_elem-1] and store in its max_value
	const void *value = find_the_max(A,num_of_elem, key_size,leq);
	memcpy(H->max_order_value, value, key_size);
	

	for(unsigned int i=num_of_elem/2; i>0; i--)
	{
		heapify(H,i);
	}	

	heapify(H,0);

	for(int i=0; i<(H)->num_of_elem; i++) 
  	{
    	unsigned int index = H->key_pos[i]; 
    	H->rev_pos[index] = i;
  	}
	
    return H;
}

void delete_heap(binheap_type *H)
{
	//dtor of heap, so I have to free its "dynamical" members
    free(H->max_order_value);
	free(H->key_pos);
	free(H->rev_pos);
	//then free H
    free(H);
}

const void *decrease_key(binheap_type *H, void* node, const void *value)
{ 
	unsigned int node_id = INDEX_OF(H, node);
    unsigned int * node_pos = REV_ADDR(H, node_id);
    unsigned int pos_key_id = *(node_pos);
    //if node not belong to H or *value->*node return NULL
    if(!VALID_NODE(H,node_id) || !(H->leq(value, node)) ) {
    	return NULL;
    }
    
    memcpy(node, value, H->key_size);
    
	if (H->num_of_elem>1)
	{
		unsigned int parent_id = PARENT(pos_key_id);
		unsigned int * parent_addr = KEY_ADDR(H, parent_id);

		void * parent = ADDR(H, *(parent_addr));

		while ((pos_key_id != 0) && (!H->leq(parent, node)) )
		{
			swap_keys(H, pos_key_id, parent_id);

			node = ADDR(H, *(parent_addr));
			pos_key_id = parent_id;
			parent_id = PARENT(pos_key_id);

			if (pos_key_id != 0)
			{
				parent_id = PARENT(pos_key_id);
				parent_addr = KEY_ADDR(H, parent_id);
				parent = ADDR(H, *(parent_addr));
			}
		}

		for(int i=0; i<(H)->num_of_elem; i++) 
  		{
    		unsigned int index = H->key_pos[i]; 
    		H->rev_pos[index] = i;
  		}
	}

	return node;
}


const void *insert_value(binheap_type *H, const void *value)
{

    if (H->max_size == H->num_of_elem){
    	return NULL;
    }
    
    if(H->num_of_elem == 0 || !(H->leq(value, H->max_order_value)) ) 
    {
    	memcpy(H->max_order_value, value, H->key_size);
    }
        
    void * new_node_addr = ADDR(H, H->num_of_elem);
	unsigned int *new_node_pos = KEY_ADDR(H, H->num_of_elem);
	unsigned int new_node_id = INDEX_OF(H, new_node_addr);

    memcpy(new_node_addr, H->max_order_value, H->key_size);
	memcpy(new_node_pos, &new_node_id, sizeof(unsigned int));
    
	H->rev_pos[H->num_of_elem] = H->num_of_elem;
    H->num_of_elem++;

    return decrease_key(H, new_node_addr, value);
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
    	
		unsigned int * addr_node = KEY_ADDR(H,node);
    	key_printer( ADDR(H, *(addr_node) ) );
    	
    	node++;
    }
    
    printf("\n");
}

