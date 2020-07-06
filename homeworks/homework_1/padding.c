#include "padding.h"
#include "matrix.h"
#include "strassen.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Given n, find_power two will return the closest power of 2 greater than n
const size_t find_power_two(const int r)
{
  int i = 0;
  int p = pow(2,i);
  while(p<r)
  {
    p = pow(2,i);
    i++;
  }
  return p;
}

/* 
 Given a matrix A of dimension A_rows x A_cols, 
 padding matrix will transform A to a nxn matrix 
 and all the elements that are new are setted at 0
*/
float **padding_matrix(float const *const *const A, 
                       const size_t A_f_row, const size_t A_f_col, 
                       const size_t A_rows, const size_t A_cols, 
                       const size_t n 
                        )
{
    float**P = allocate_matrix(n,n);
    
    for(size_t i=0; i<A_rows; i++)
    {
        for(size_t j=0; j<A_cols; j++)
        {
            P[i][j]= A[A_f_row+i][A_f_col+j];
        }

        for (size_t j = A_cols; j < n; j++)
        {
            P[i][j]= 0;
        }
        
    }

    for (size_t i = A_rows; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            P[i][j] = 0;
        }
    }

    return P;
}

void strassen_matrix_multiplication_padding_sq_aux(float **C, float const *const *const A,
                                               float const *const * const B,
                                               const size_t C_f_row, const size_t C_f_col,
                                               const size_t A_f_row, const size_t A_f_col,
                                               const size_t B_f_row, const size_t B_f_col,
                                               const size_t n)
{
    const size_t p = find_power_two(n);

    if(p == n)
    {
        strassen_matrix_multiplication(C, A, B, n);
    }

    else
    {
        float **A_p = padding_matrix(A, A_f_row, A_f_col, n, n, p);
        float **B_p = padding_matrix(B, B_f_row, B_f_col, n, n, p);
        float **C_p = allocate_matrix(p, p);
        
        strassen_matrix_multiplication(C_p, 
                                       (float const *const *const)A_p,
                                       (float const *const *const)B_p, 
                                       p);
        
        deallocate_matrix(A_p, p);
        deallocate_matrix(B_p, p);

        for(size_t i=0; i<n; i++)
        {
            memcpy(C[i], C_p[i], sizeof(float)*n);
        }
        deallocate_matrix(C_p, p);
    }

}

void strassen_matrix_multiplication_padding_sq(float **C, float const *const *const A,
                                               float const *const *const B, size_t n)
{
    strassen_matrix_multiplication_padding_sq_aux(C, A, B,
                                                  0, 0,
                                                  0, 0,
                                                  0, 0,
                                                  n);
}