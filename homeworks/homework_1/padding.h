#ifndef __PADDING__

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "strassen.h"

const size_t find_power_two(const int n);

float **padding_matrix(float const *const *const A, 
                       const size_t A_f_row, const size_t A_f_col, 
                       const size_t A_r, const size_t A_c, 
                       const size_t n 
                        );

void strassen_matrix_multiplication_padding_sq_aux(float **C, float const *const *const A,
                                               float const *const * const B,
                                               const size_t C_f_row, const size_t C_f_col,
                                               const size_t A_f_row, const size_t A_f_col,
                                               const size_t B_f_row, const size_t B_f_col,
                                               const size_t n);

void strassen_matrix_multiplication_padding_sq(float **C, float const *const *const A,
                                               float const *const *const B, size_t n);




#endif //__PADDING__