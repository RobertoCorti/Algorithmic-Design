#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "dijkstra.h"
#include "binheap.h"

#define INFTY 999999

/* 
 * Init ssp function; initialization for Dijkstra Algorithm.
 */
void init_sssp(Graph* G)
{
    for (size_t i = 0; i < G->num_nodes; i++)
    {
        (G->V[i]).id = i;
        (G->V[i]).dist = INFTY;
        (G->V[i]).pred = NULL;
    }
    
}

/*
 * Relax function; check dist(u) + weight < dist(v) and in true case, it updates dist(v)
 */
void relax(Node* u, Node* v, unsigned int weight)
{
    if (u->dist + weight < v->dist)
    {
        v->dist = u->dist + weight;
        v->pred = u;
    }
    
}


/*
 * Dijkastra Algorithm in a graph g from a source in the position source_id (Array-queue)
 */
void dijkstra(Graph* g, unsigned int source_id)
{
    init_sssp(g);
    Node * source = node(g, source_id);
    source->dist = 0;
    
    Queue queue = build_queue(g->V, g->num_nodes);
    Queue *q = &queue;
    
    while ( !(is_empty(q)) )
    {
        Node * u = extract_minimum(q);
        unsigned int num_neigh = num_neighbours(g, u);
        Node** neigh = neighbours(g, u);

        for (size_t i = 0; i < num_neigh; i++)
        {
            relax(u, neigh[i], weight(g, u, neigh[i]));
        }
        
        free(neigh);
    }
    
}

/*
 * Compare a's distance with b's distance
 */
int compare_dist(const void *a, const void *b)
{
    Node* s = (Node*)a;
    Node* d = (Node*)b;
    return leq_int((void*)&(s->dist), (void*)&(d->dist));
}

/*
 * Dijkastra Algorithm in a graph g from a source in the position source_id (binary heap-queue)
 */
void dijkstra_heap(Graph * g, unsigned int source_id)
{
    init_sssp(g);

    Node * source = node(g, source_id);
    source->dist = 0;
    binheap_type* queue = build_heap(g->V, g->num_nodes, g->num_nodes, sizeof(Node), compare_dist);
    
    while ( !(is_heap_empty(queue)) )
    {
        Node * u = (Node*)extract_min(queue);
        unsigned int num_neigh = num_neighbours(g, u);
        Node** neigh = neighbours(g, u);
        for (size_t i = 0; i < num_neigh; i++)
        {
            relax(u, neigh[i], weight(g, u, neigh[i]));
        }
        
        heapify(queue, 0);
        free(neigh);
    }

    delete_heap(queue);
    
}