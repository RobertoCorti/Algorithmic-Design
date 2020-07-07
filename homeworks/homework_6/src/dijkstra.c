#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "dijkstra.h"

#define INFTY 999999

/* 
 * Init ssp function; initialization for Dijkstra Algorithm.
 */
void init_sssp(Graph* G)
{
    for (size_t i = 0; i < G->num_nodes; i++)
    {
        G->V[i].id = i;
        G->V[i].dist = INFTY;
        G->V[i].pred = NULL;
    }
    
}

/*
 * Relax function; check dist[u] + weight < dist[v] and in true case, it updates v distance
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
 * Dijkastra Algorithm in a graph g from a source in the position source_id
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