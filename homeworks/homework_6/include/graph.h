#ifndef __GRAPH__


typedef struct Node {
  
  unsigned int id; 
  unsigned int dist; 
  struct Node *pred; 

} Node;


typedef struct Graph
{
    unsigned int num_nodes;
    Node * V;  //vertex
    unsigned int ** E; //adjacency matrix
} Graph;

Graph build_graph(unsigned int n, Node * nodes, unsigned int ** weights);

int weight(Graph* g, Node* s, Node* d);

unsigned int num_neighbours(Graph* g, Node* node);

Node ** neighbours(Graph *g, Node* node);

Node* node(Graph* g, int id);

void print_graph(Graph* g);

#endif //__GRAPH__