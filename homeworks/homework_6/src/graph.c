#include<stdlib.h>
#include<stdio.h>

#include "graph.h"

#define INFTY 999999

/*  
 * Construction of a graph  
 */
Graph build_graph(unsigned int n, Node * nodes, unsigned int ** weights)
{
    Graph g;
    g.num_nodes = n;
    g.V = nodes;
    g.E = weights;

    return g;
}


/*  
 * Returns weight associated with the edge (s,d). 
 */
int weight(Graph* g, Node* s, Node* d)
{
    
    int check_s = s->id > g->num_nodes || s->id < 0;
    int check_d = d->id > g->num_nodes || d->id < 0;

    if (check_s || check_d )
    {
        printf("error: index out of %d\n", g->num_nodes);
        return -9999;
    }
    
    else{
        return g->E[s->id][d->id];
    }
}

/* 
 * Returns number of neighbours of a node in the graph
 */
unsigned int num_neighbours(Graph* g, Node* node)
{
    int m=0;
    for (size_t i = 0; i < g->num_nodes; i++)
    {
        int w = weight(g, node, &(g->V)[i]);    
        if(w < INFTY && (g->V)[i].id != node->id)
        {
            m++;
        }
    }

    return m;

}

/* 
 * Returns neighbours nodes of the node passed as argument
 */
Node** neighbours(Graph* g, Node* node)
{
    unsigned int where_neighbours[g->num_nodes];
    int m=0;
    for (size_t i = 0; i < g->num_nodes; i++)
    {
        int w = weight(g, node, &(g->V)[i]);    
        if(w < INFTY && (g->V)[i].id != node->id)
        {
            where_neighbours[i] = i;
            m++;
        }
        else
        {
            where_neighbours[i] = 0;
        }
    }

    Node ** neighbours = (Node**)malloc(sizeof(Node*)*m);
    int s=0;
    for (size_t i = 0; i < g->num_nodes; i++)
    {
        if (where_neighbours[i])
        {
            neighbours[s] = &(g->V)[i];
            s++; 
        }
    }
    
    return neighbours;
}

/* 
 * Returns id-th node
 */
Node* node(Graph* g, int id)
{
  for(size_t i=0; i<g->num_nodes; i++)
  {
    if(g->V[i].id==id) 
    { 
        return &(g->V[i]); 
    }
  }
  return NULL; 
}

void print_graph(Graph* g)
{
    int size = g->num_nodes;
    printf("\n--------------------------------------------\n");
    printf("                  GRAPH                      \n");
    printf("\nNumber of nodes: %d\n", size);
    
    printf("\nAdjacency matrix:\n");
    for(size_t i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(g->E[i][j]==INFTY)
                printf("NULL\t");
            else
                printf("%d\t", g->E[i][j]);
        }
        printf("\n");
    }

    for(size_t i=0; i<size; i++)
    {
        Node node = g->V[i];

        printf("\nnode %d: dist=%d", node.id, node.dist);
        
        if((node.pred)!=NULL)
            printf(", pred=%d", node.pred->id);
        else
            printf(", ");

    }

    printf("\n");

    printf("\n--------------------------------------------\n");
}