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
void swapi(int *v, const int rank, const int i, const int j){
    assert(i < rank);
    assert(j < rank);

    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

/* Set every entry of the rank x rank matrix A to 0.0. */
void zeros(double **A, const int rank){
    for(int i = 0; i < rank; i++){
        for(int j = 0; j < rank; j++){
            A[i][j] = 0;
        }
    }
}

/* Set the main diagonal of A to 1.0, leaving off-diagonal entries unchanged. */
void ones(double **A, const int rank){
    for(int i = 0; i < rank; i++){
        A[i][i] = 1;
    }
}

/* Allocate a row x col double matrix via calloc (all entries start at 0.0).
 * The outer pointer array is NULL-checked; inner row callocs are not. */
double **matrix_alloc(const int row, const int col){
    double **A = calloc(row, sizeof(double*));
    if(A == NULL)
        perror("[!] no more memory");

    for (int i = 0; i < row; i++) {
        A[i] = calloc(col, sizeof(double));
    }

    return A;
}

/* Free each row array then the outer pointer array.
 * Do NOT call on matrices whose row pointers point to stack memory. */
void matrix_free(double **A, const int row){
    for (int i = 0; i < row; i++) {
        free(A[i]);
    }
    free(A);
}

/* Swap row pointers A[i] and A[j] in O(1) (no element copy). Asserts i,j < rank. */
void swap_row(double **A, const int rank, const int i, const int j){
    assert(i < rank);
    assert(j < rank);

    double *tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
