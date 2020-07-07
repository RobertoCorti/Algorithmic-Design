#include <stdio.h>
#include "test.h"
#include "matrix.h"
#include "strassen.h"
#include "padding.h"
#include "rectangular.h"

int main(int argc, char *argv[]) {
    size_t n = 1 << 12; // 2^12 
    float **A = allocate_random_matrix(n, n);
    float **B = allocate_random_matrix(n, n);
    float **C0 = allocate_matrix(n, n);
    float **C1 = allocate_matrix(n, n);

    
    printf("n\tStrassen's Alg.\tNaive Alg.\tSame result\n");
    for (size_t j = 1; j <= n; j = 2*j) 
    {   
        printf("%ld\t", j);
        fflush(stdout);   
        printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, j));
        fflush(stdout);
        printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, j));
        fflush(stdout);

        printf("%d\n", same_matrix((float const *const *const)C0,
                                 (float const *const *const)C1, j, j));
    }
    

    
    int m, l, k;

    printf("\nPlease insert dimensions of the matrix to be multiplied. \nC(mxk) =  A(mxl) X B(lxk)\n");
    printf("\nm = ");
    scanf("%u", &m);
    printf("\nl = ");
    scanf("%u", &l);
    printf("\nk = ");
    scanf("%u", &k);

    float** A1 = allocate_random_matrix(m,l);
    float** B1 = allocate_random_matrix(l,k);
    float** C = allocate_matrix(m,k);
    float** CC = allocate_matrix(m,k);

    
  
    printf("Naive Mult.\t General Strassen\t  Same result\n");
    
    strassen_rectangular_multiplication(CC,(float const *const *const)A1, m, l, (float const *const *const)B1, l, k);

    naive_rectangular_matrix_multiplication(C, (float const *const *const)A1, 
                                            (float const *const *const)B1,
                                             m, l, k);

    printf("\t\t\t\t\t\t %d\n", same_matrix((float const *const *const)CC,
                             (float const *const *const)C, m, k));
    

    printf("n\tStrassen Alg.\tOpt.Strassen Alg.\tSame result\n");
    for (size_t j = 1; j <= n; j = 2*j) 
    {   
        printf("%ld\t", j);
        fflush(stdout);   
        printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, j));
        fflush(stdout);
        printf("%lf\t", test(strassen_matrix_multiplication_opt, C0, A, B, j));
        fflush(stdout);
        

        printf("%d\n", same_matrix((float const *const *const)C0,
                                 (float const *const *const)C1, j, j));
    }

    deallocate_matrix(A, n);
    deallocate_matrix(B, n);
    deallocate_matrix(C0, n);
    deallocate_matrix(C1, n);
    

    return 0;
}