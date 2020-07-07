#ifndef __DIJKSTRA__

#include "queue.h"

void init_sssp(Graph* G);

void relax(Node* u, Node* v, unsigned int weight);

void dijkstra(Graph* g, unsigned int source_id);




#endif // __DIJKSTRA__