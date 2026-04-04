/*
 * linalg.c -- Low-level matrix primitives: alloc/free, initialization, swaps.
 *
 * All matrices are represented as double** (array of row pointers).
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* Absolute value of a double. Avoids the <math.h> / -lm dependency. */
double dabs(double a){
    if (a >= 0) return a;
    return a*-1;
}

/* Swap row pointers A[i] and A[j] in O(1) (no element copy). Asserts i,j < dim. */
void swap_row(double **A, const size_t dim, const size_t i, const size_t j){
    assert(i < dim);
    assert(j < dim);

    double *tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

/* Swap v[i] and v[j] in a size_t array. Asserts i,j < dim. */
void swap_vect(size_t *v, const size_t dim, const size_t i, const size_t j){
    assert(i < dim);
    assert(j < dim);

    size_t tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

/* Apply permutation matrix to another matrix, the permutation matrix must be flatted. */
void perm_matrix(double **A, size_t *perm, const size_t dim){
    for(size_t i = 0; i < dim; i++)
        swap_row(A, dim, i, perm[i]);
}

/* Apply permutation matrix to a vector, the permutation matrix must be flatted. */
void perm_vect(size_t *v, size_t *perm, const size_t length){
    for(size_t i = 0; i < length; i++)
        swap_vect(v, length, i, perm[i]);
}

/* Set every entry of the dim x dim matrix A to 0.0. */
void zeros(double **A, const size_t dim){
    for(size_t i = 0; i < dim; i++){
        for(size_t j = 0; j < dim; j++){
            A[i][j] = 0;
        }
    }
}

/* Set the main diagonal of A to 1.0, leaving off-diagonal entries unchanged. */
void eye(double **A, const size_t dim){
    for(size_t i = 0; i < dim; i++){
        A[i][i] = 1;
    }
}