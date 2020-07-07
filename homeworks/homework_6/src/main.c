#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dijkstra.h"

#define INFTY 999999

int main()
{
    // reproducing slides' example 

    unsigned int size = 6;
    unsigned int ** adj_mat = (unsigned int **)malloc(sizeof(unsigned int *)*size);

    for (size_t i = 0; i < size; i++)
    {
        adj_mat[i] = (unsigned int *)malloc(sizeof(unsigned int)*size);

        for (size_t j = 0; j < size; j++)
        {
            adj_mat[i][j] = INFTY;
            //printf("%d \t", adj_mat[i][j]);
        }
        //printf("\n");
    }
    
    
    //printf("\n");

    Node * nodes = (Node*)malloc(sizeof(Node)*size);

    adj_mat[0][1] = 1;
    adj_mat[0][2] = 5;
    adj_mat[1][5] = 15;
    adj_mat[2][3] = 2;
    adj_mat[3][4] = 1;
    adj_mat[4][5] = 3;
    

    Graph graph = build_graph(size, nodes, adj_mat);
    
    print_graph(&graph);

    printf("\n--------------------------------------------\n");
    printf("    ...performing DIJKSTRA ALGORITHM...      \n");
    printf("--------------------------------------------\n");
    dijkstra(&graph, 0);

    print_graph(&graph);


    return 0;
}

