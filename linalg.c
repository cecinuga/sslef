/*
 * linalg.c -- Low-level matrix primitives: alloc/free, initialization, swaps.
 *
 * All matrices are represented as double** (array of row pointers).
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Absolute value of a double. Avoids the <math.h> / -lm dependency. */
double dabs(double a){
    if (a >= 0) return a;
    return a*-1;
}

/* Swap v[i] and v[j] in an integer array. Asserts i,j < rank. */
void swapi(int *v, const size_t rank, const size_t i, const size_t j){
    assert(i < rank);
    assert(j < rank);

    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

/* Set every entry of the rank x rank matrix A to 0.0. */
void zeros(double **A, const size_t rank){
    for(size_t i = 0; i < rank; i++){
        for(size_t j = 0; j < rank; j++){
            A[i][j] = 0;
        }
    }
}

/* Set the main diagonal of A to 1.0, leaving off-diagonal entries unchanged. */
void ones(double **A, const size_t rank){
    for(size_t i = 0; i < rank; i++){
        A[i][i] = 1;
    }
}

/* Swap row pointers A[i] and A[j] in O(1) (no element copy). Asserts i,j < rank. */
void swap_row(double **A, const size_t rank, const size_t i, const size_t j){
    assert(i < rank);
    assert(j < rank);

    double *tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
