#include <stdlib.h>
#include <stdio.h>
#include "linalg.h"
#include "utils.h"

int main(void){
    size_t dim = 3;
    double **A = mmalloc(dim, dim);

    double colA0[] = {1, 2, 3};
    double colA1[] = {1, 1, -1};
    double colA2[] = {1, 0, 2}; 

    double **B = mmalloc(dim, dim);
    eye(B, dim);

    double *vect = calloc(dim, sizeof(double));
    vect[0] = 1; vect[1] = 2; vect[2] = 3;

    A[0] = (double*)&colA0;
    A[1] = (double*)&colA1;
    A[2] = (double*)&colA2;

    printf("matrix: \n");
    printm(A, dim);

    printf("matrix: \n");
    printm(B, dim);

    printf("result of multiplication: \n");
    double **out = mmalloc(dim, dim);
    mmmul(A, B, out, dim);
    printm(out, dim);
    mfree(out, dim);

    return 0;
}