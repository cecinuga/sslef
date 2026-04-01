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

/* Apply permutation matrix to another matrix, the permutation matrix must be flatted. */
void perm_matrix(void **A, size_t *perm, const size_t rank){
    for(size_t i = 0; i < rank; i+=2)
        swap_row(A, rank, perm[i], perm[i+1]);
}

/* Apply permutation matrix to a vector, the permutation matrix must be flatted. */
void perm_vect(void *v, size_t *perm, const size_t length){
    for(size_t i = 0; i < length; i+=2)
        swap_vect(v, length, perm[i], perm[i+1]);
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
void eye(double **A, const size_t rank){
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

/* Swap v[i] and v[j] in an integer array. Asserts i,j < rank. */
void swap_vect(int *v, const size_t rank, const size_t i, const size_t j){
    assert(i < rank);
    assert(j < rank);

    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
