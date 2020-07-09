#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include "matrix.h"
#include "strassen.h"
#include "padding.h"


/* Implementation of the naive algorithm 
   of C=AxB where, A nxm, B mxk and C nxk matrices
*/
void naive_rectangular_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t A_rows, //number of rows of A
                                const size_t A_cols, //number of columns of A = number of rows of B
                                const size_t B_cols)
{
    for (size_t i = 0; i < A_rows; i++)
    {
       for (size_t j = 0; j < B_cols; j++)
       {
           float value = 0.0;
           for (size_t k = 0; k < A_cols; k++)
           {
               value += A[i][k]*B[k][j];
           }

        C[i][j] = value;
       }
       
    }
}

/* 
   Given A of size A_rows x A_cols,
   partition matrix will generate an array of matrices of sizes block_rows x block_cols
   by_row will tell us if the partition has to be done by row or by column
   1-> matrix has to be divided by row, 0--> matrix has to be divided by column
*/
float*** partition_matrix(float const *const *const A, 
                          const size_t A_rows, const size_t A_cols, 
                          const size_t block_rows, const size_t block_cols, 
                          const size_t n, 
                          int by_row 
                          )
{
    int num_blocks = 0;

    if (by_row == 1)
    {
        if ( A_rows % block_rows == 0  )
        {
            num_blocks = A_rows / block_rows;
        }
        else
        {
            num_blocks = A_rows / block_rows + 1;
        }
        
        unsigned int where_to_start[num_blocks]; 
        
        for(size_t i=0; i<num_blocks; i++)
        {
            where_to_start[i]=i*block_rows;
        }

        int where_to_end;

        if (where_to_start[num_blocks-1] + block_rows > A_rows-1)
        {
            where_to_end = A_rows-1;
        }

        else
        {
            where_to_end = where_to_start[num_blocks-1] + block_rows -1;
        }
        
        float *** A_blocks = (float ***)malloc(sizeof(float **) * num_blocks);
        
        for (size_t i = 0; i < num_blocks; i++)
        {
            if (i != num_blocks -1)
            {
                A_blocks[i] = padding_matrix(A, where_to_start[i], 0, block_rows, block_cols, n);
            }

            else
            {
                A_blocks[i] = padding_matrix(A, where_to_start[i], 0, (where_to_end-where_to_start[i]+1), block_cols, n);
            }
        }

        return A_blocks;
        
    }

    else if(by_row == 0)
    {
        if ( A_cols % block_cols == 0 )
        {
            num_blocks = A_cols / block_cols;
        }
        else
        {
            num_blocks = A_cols / block_cols + 1;
        }

        unsigned int where_to_start[num_blocks]; 
        
        for(size_t i=0; i<num_blocks; i++)
        {
            where_to_start[i]=i*block_cols;
        }
        
        int where_to_end;

        if (where_to_start[num_blocks-1] + block_cols > A_cols-1)
        {
            where_to_end = A_cols-1;
        }
        else
        {
            where_to_end = where_to_start[num_blocks-1] + block_cols -1;
        }
        //printf("\nwhere_to_end=%d\n", where_to_end);
        float *** A_blocks = (float ***)malloc(sizeof(float **) * num_blocks);
        
        for (size_t i = 0; i < num_blocks; i++)
        {
            if (i != num_blocks -1)
            {
                A_blocks[i] = padding_matrix(A, 0, where_to_start[i], block_rows, block_cols, n);
            }

            else
            {
                A_blocks[i] = padding_matrix(A, 0, where_to_start[i], block_rows, (where_to_end-where_to_start[i]+1), n);
            }
        }

        return A_blocks;
    }

    else
    {
        printf("ERROR: by_row must be 0/1.\n");
        return NULL;
    }
     
}

void strassen_rectangular_multiplication(float** C, float const *const *const A,
                                          const size_t A_rows, const size_t A_cols, 
                                          float const *const *const B,
                                          const size_t B_rows, const size_t B_cols 
                                         )
{
    if (A_rows==A_cols && B_rows==B_cols)
    {
        strassen_matrix_multiplication_padding_sq(C, A, B, A_rows);
    }

    else
    { 
        size_t BA_r = A_rows;
        size_t BB_r = BA_r;
        size_t BB_c = B_cols;

        size_t n = (BA_r>BB_c)? find_power_two(BA_r) : find_power_two(BB_c); 
        // square dimension of every block
        
        float*** A_p = partition_matrix(A, A_rows, A_cols, BA_r, BA_r, n, 0);
        //A will be divided by column in blocks of dim BA_r x BA_r, then padded to sq. matrices of n
        float*** B_p = partition_matrix(B, B_rows, B_cols, BB_r, BB_c, n, 1);
        //B will be divided by row in blocks of dim BB_r x BB_r, then padded to sq. matrices of n
        int n_blocks = A_cols/BA_r+1;
        
        float** D = allocate_matrix(n,n); //this will be returned
        float** C_aux = allocate_matrix(n,n); //this is auxiliary, for partial results


        for(size_t i=0; i<n_blocks; i++)
        {
            naive_matrix_multiplication(C_aux, (float const *const *const)A_p[i], (float const *const *const)B_p[i], n); 
            sum_matrix(D,(float const *const *const)D,(float const *const *const)C_aux, n);
        }

        for (size_t i = 0; i < n_blocks; i++) 
        {
            deallocate_matrix(A_p[i], n);
            deallocate_matrix(B_p[i], n);
        }
    
        free(A_p);
        free(B_p);
        deallocate_matrix(C_aux, n);

        for(size_t i=0; i<A_rows; i++)
        {
            memcpy(C[i], D[i], sizeof(float)*B_cols);
        }
        deallocate_matrix(D, n);
    }

}
