#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dijkstra.h"

#define INFTY 999999

int main()
{
    // reproducing slides' example 
    
    printf("\n--------------------------------------------\n");
    printf("        DIJKSTRA ALGORITHM       \n");
    printf("--------------------------------------------\n");

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

    Node * nodes_a = (Node*)malloc(sizeof(Node)*size);
    Node * nodes_h = (Node*)malloc(sizeof(Node)*size);

    adj_mat[0][1] = 1;
    adj_mat[0][2] = 5;
    adj_mat[1][5] = 15;
    adj_mat[2][3] = 2;
    adj_mat[3][4] = 1;
    adj_mat[4][5] = 3;
    

    Graph graph_a = build_graph(size, nodes_a, adj_mat);
    Graph graph_h = build_graph(size, nodes_h, adj_mat);
    printf("\n-INITIAL GRAPH:\n");
    print_graph(&graph_a);

    printf("\n-ARRAY QUEUE:\n");
    dijkstra(&graph_a, 0);
    print_graph(&graph_a);

    printf("\n-HEAP QUEUE:\n");
    dijkstra_heap(&graph_h, 0);
    print_graph(&graph_h);
    
    struct timespec start, end; 
    unsigned int s1 = 50000;
    unsigned int** adj_mat_1 = (unsigned int **)malloc(sizeof(unsigned int *)*s1);  
    
    for(size_t i=0; i<s1; i++)
    {
        adj_mat_1[i] = (unsigned int *)malloc(sizeof(unsigned int)*s1);
    }

    for (size_t i = 0; i < s1; i++)
    {
        for(size_t j=0; j< s1; j++)
        {
          if((i+j)<2500)
            adj_mat_1[i][j]= i+j; 
          if((i+j)>300)
            adj_mat_1[j][i] = i+j+5;
        }
    }
    
    
    Node*nodes_1 = (Node*)malloc(sizeof(Node)*s1);
    Node*nodes_2 = (Node*)malloc(sizeof(Node)*s1);

    Graph g1 = build_graph(s1, nodes_1, adj_mat_1);
    Graph g2 = build_graph(s1, nodes_2, adj_mat_1);

    // printf("\n");
    // printf("--------------------------------------------\n");
    // printf("              TEST             \n\n");
    
    printf("size\tArray\tHeap\n");
    for(size_t i=0; i<10; i++)
    {
        g1.num_nodes = s1/(1<<(10-i));  //<==> 2^(10-i) (2^10, ...., 2^0)
        g2.num_nodes = s1/(1<<(10-i));

        printf("%d", g1.num_nodes);
        
        clock_gettime(CLOCK_REALTIME, &start);
        dijkstra(&g1, 0);
        clock_gettime(CLOCK_REALTIME, &end);

        printf("\t%lf", (end.tv_sec-start.tv_sec) +
                        (end.tv_nsec-start.tv_nsec)/1E9 );

        clock_gettime(CLOCK_REALTIME, &start);
        dijkstra_heap(&g2, 0);
        clock_gettime(CLOCK_REALTIME, &end);

        printf("\t%lf\n", (end.tv_sec-start.tv_sec) +
                        (end.tv_nsec-start.tv_nsec)/1E9 );
        
    }
    printf("\n");
    
    free(adj_mat_1);
    free(g1.V);
    free(g2.V);
    
    return 0;
}

