#ifndef __DIJKSTRA__

#include "queue.h"
#include "binheap.h"

void init_sssp(Graph* G);

void relax(Node* u, Node* v, unsigned int weight);

int compare_dist(const void *s, const void *d);

void dijkstra(Graph* g, unsigned int source_id);

void dijkstra_heap(Graph * g, unsigned int source_id);




#endif // __DIJKSTRA__