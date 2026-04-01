/*
 * solver.c -- Entry point and high-level solver routines.
 *
 * partial_pivoting() -- row-permutation step of PA = LU
 * elimination()      -- Doolittle LU factorization (stale-coefs bug remains)
 * main()             -- hard-coded 5x5 test, prints pivoted A, L, and U
 *
 * Missing: forward/back substitution; the system is factored but not solved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linalg.h"
#include "utils.h"

/*
 * partial_pivoting -- For each column k, finds the row j >= k with the largest
 * |A[j][k]| and swaps it to position k. Records each swap in permutation[].
 */
void partial_pivoting(double **A, size_t *permutation, const size_t rank){
    int max_i = 0;
    double max = 0;

    for (size_t i = 0; i < rank; i++){
        max_i = i;
        max = dabs(A[i][i]);
        for (size_t j = i; j < rank; j++){
            if ( dabs(A[j][i]) > max ){
                max_i = j;
                max = dabs(A[j][i]);
            }
        }

        swap_vect(permutation, rank, i, max_i);
        swap_row(A, rank, i, max_i);
    }
}

/*
 * elimination -- Doolittle LU factorization of coefs into L (unit lower
 * triangular) and U (upper triangular) such that coefs = L * U.
 *
 * For each pivot column k:
 *   L[i][k] = coefs[i][k] / coefs[k][k]              (row multiplier)
 *   U[i][j] = coefs[i][j] - L[i][k] * coefs[k][j]    (Schur update)
 *
 * BUG: reads original `coefs` at every step instead of the evolving U.
 * For k >= 1, coefs[i][k] and coefs[k][j] no longer reflect prior elimination
 * steps; the algorithm must use U[i][k] / U[k][k] and U[i][j] - L[i][k]*U[k][j].
 * Also, only U[0] is pre-populated; rows 1..rank-1 of U must be copied from
 * coefs before the loop begins.
 */
void elimination(double **coefs, double **U, double **L, const size_t rank){
    /* Row 0 needs no elimination: copy directly to U */
    for(size_t i = 0; i < rank; i++)
        U[0][i] = coefs[0][i];

    double elCoef = 0;
    for(size_t k = 0; k < rank; k++){
        for(size_t i = k+1; i < rank; i++){
            elCoef = U[i][k]/U[k][k];  
            L[i][k] = elCoef;
            for(size_t j = k; j < rank; j++){
                U[i][j] -= U[k][j]*elCoef; 
            }
        }
    }
}

/*
 * main -- Hard-coded 5x5 demonstration: row-reorders a matrix, factors it into
 * L and U, then prints the results.
 *
 * coefs rows point to stack arrays (col0..col4); only the outer pointer array
 * is heap-allocated, so only `coefs` itself (not coefs[i]) is freed.
 *
 * consts (RHS vector b) is allocated but unused -- no solve step exists yet.
 */
int main(void) {
    const size_t rank = 3;

    size_t *permutation = calloc(rank, sizeof(size_t));
    double **coefs = calloc(rank, sizeof(double*)); 
    double **upper = matrix_alloc(rank, rank);
    double **lower = matrix_alloc(rank, rank);
    double *consts = calloc(rank, sizeof(double)); 

    double col0[] = {1, 2, 5};
    double col1[] = {3, 8, 10};
    double col2[] = {-4.5, -4, 3}; 


    coefs[0] = (double*)&col0;
    coefs[1] = (double*)&col1;
    coefs[2] = (double*)&col2;

    for (size_t i = 0; i < rank; i++ ) 
        permutation[i] = i;

    matrix_copy(upper, coefs, rank);
    eye(lower, rank);

    printf("original matrix: \n");
    print_matrix(coefs, rank);

    printf("permutation flatten matrix: \n");
    print_stvector(permutation, rank);

    printf("applied permutation matrix: \n");
    perm_matrix(coefs, permutation, rank);
    print_matrix(coefs, rank);

    printf("------------------------------\n");
    printf("\nafter partial pivoting: \n");
    partial_pivoting(coefs, permutation, rank);
    print_matrix(coefs, rank);

    printf("------------------------------\n");
    printf("\npermutation flatted matrix: \n");
    print_stvector(permutation, rank);

    elimination(coefs, upper, lower, rank);

    printf("------------------------------\n");
    printf("\nupper triangle: \n");
    print_matrix(upper, rank);

    printf("------------------------------\n");
    printf("\nlower triangle: \n");
    print_matrix(lower, rank);

    free(coefs); free(permutation); free(consts);
    matrix_free(lower, rank); matrix_free(upper, rank);

    return 0;
}


