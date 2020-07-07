#ifndef __RECTANGULAR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "matrix.h"
#include "strassen.h"
#include "padding.h"


void naive_rectangular_matrix_multiplication(float **C, float const *const *const A,
                                float const *const *const B,
                                const size_t A_rows, 
                                const size_t A_cols, 
                                const size_t B_cols); 
 
float*** partition_matrix(float const *const *const A, 
                          const size_t A_r, const size_t A_c, 
                          const size_t B_r, const size_t B_c, 
                          const size_t n, 
                          int by_row // 1-> matrix has to be divided by row, 0--> matrix has to be divided by column
                          );

void strassen_rectangular_multiplication(float** C, float const *const *const A,
                                          const size_t A_rows, const size_t A_cols, 
                                          float const *const *const B,
                                          const size_t B_rows, const size_t B_cols 
                                         );

#endif //__RECTANGULAR__