#ifndef __QUEUE__

#include "graph.h"

typedef struct Queue
{
    Node ** nodes;
    unsigned int num_nodes;

} Queue;

Queue build_queue(Node* nodes, unsigned int n);

void delete_queue(Queue q);

int is_empty(Queue* q);

Node* extract_minimum(Queue *q);




#endif //__GRAPH__