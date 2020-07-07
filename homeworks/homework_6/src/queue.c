#include <stdlib.h>

#include "queue.h"

/*  
 * Construction of a queue with n nodes given by argument   
 */
Queue build_queue(Node* nodes, unsigned int n)
{
    Queue q;
    Node** nodes_aux = (Node**)malloc(sizeof(Node*)*n);  

    for(size_t i=0; i<n; i++)
    {
      nodes_aux[i] = &(nodes[i]);
    }

    q.num_nodes = n;
    q.nodes = nodes_aux;

    return q;
}

/* 
 * Deletion of a queue
*/
void elete_queue(Queue q)
{
    free(q.nodes);
}


/* 
 * Check for empytness of a queue
*/
int is_empty(Queue* q)
{
    return q->num_nodes == 0;
}

/* 
 * Dequeue operation for ith element of the queue
*/
void dequeue(Queue * q, unsigned int id)
{
    Node *aux = q->nodes[id];
    q->nodes[id] = q->nodes[q->num_nodes-1];
    q->nodes[q->num_nodes-1] = aux; 

    q->num_nodes--;
}

/* 
 * Extraction from queue of the node whose distance is minimum
*/
Node* extract_minimum(Queue *q)
{
    unsigned int min = q->nodes[0]->dist;
    int min_id = 0;

    for(size_t i=0; i<q->num_nodes; i++)
    {
      if(q->nodes[i]->dist < min)
      {
        min = q->nodes[i]->dist;
        min_id = i;
      }
    }

    Node* min_node = q->nodes[min_id];
    dequeue(q, min_id);
    return min_node;
}
