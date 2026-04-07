/*
 * solver.c -- Entry point and high-level solver routines.
 *
 * pivoting() -- row-permutation step of PA = LU
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
 * pivoting -- For each column k, finds the row j >= k with the largest
 * |A[j][k]| and swaps it to position k. Records each swap in permutation[].
 */
void pivoting(double **A, double *rhs, size_t *permutation, const size_t dim){
    int max_i = 0;
    double max = 0;

    for (size_t i = 0; i < dim; i++){
        max_i = i;
        max = dabs(A[i][i]);
        for (size_t j = i; j < dim; j++){
            if ( dabs(A[j][i]) > max ){
                max_i = j;
                max = dabs(A[j][i]);
            }
        }

        swap(rhs, dim, i, max_i);
        swap(permutation, dim, i, max_i);
        swap(A, dim, i, max_i);
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
 * For k >= 1, coefs[i][k] and coefs[k][j] no longer reflect prior elimination
 * steps; the algorithm must use U[i][k] / U[k][k] and U[i][j] - L[i][k]*U[k][j].
 * Also, only U[0] is pre-populated; rows 1..dim-1 of U must be copied from
 * coefs before the loop begins.
 */
void elimination(double **A, double **U, double **L, double *rhs, const size_t dim){
    /* Copy all rows of coefs (post-pivoting) into U before factoring */
    mcopy(U, A, dim);
    
    double elCoef = 0;
    for(size_t k = 0; k < dim; k++){
        for(size_t i = k+1; i < dim; i++){
            elCoef = U[i][k]/U[k][k];  
            L[i][k] = elCoef;
            rhs[i] -= rhs[k]*elCoef;

            for(size_t j = k; j < dim; j++){
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
    const size_t dim = 3;

    size_t *permutation = calloc(dim, sizeof(size_t));
    double **coefs = calloc(dim, sizeof(double*)); 
    double **upper = mmalloc(dim, dim);
    double **lower = mmalloc(dim, dim);
    double *rhs = calloc(dim, sizeof(double)); 

    rhs[0] = 1; rhs[1] = 2; rhs[2] = 3;

    double col0[] = {1, 2, 5};
    double col1[] = {3, 8, 10};
    double col2[] = {-4.5, -4, 3}; 

    coefs[0] = (double*)&col0;
    coefs[1] = (double*)&col1;
    coefs[2] = (double*)&col2;

    for (size_t i = 0; i < dim; i++ ) 
        permutation[i] = i;

    eye(lower, dim);

    printf("------------------ORIGINAL-------------------\n");
    printf("\nA: \n");
    printm(coefs, dim);

    printf("\nrhs: \n");
    printv(rhs, dim);


    // -- PARTIAL PIVOTING ---
    printf("------------PARTIAL PIVOTING------------------\n");
    printf("\nA: \n");
    pivoting(coefs, rhs, permutation, dim);
    
    printm(coefs, dim);
    printv(rhs, dim);
    printf("\npermutation flatted matrix: \n");
    printv(permutation, dim);

    // -- ELIMINATION ---
    elimination(coefs, upper, lower, rhs, dim);

    // -- LOGGING --
    printf("-----------------ELIMINATION--------------------\n");
    printf("\nupper triangle: \n");
    printm(upper, dim);

    printf("------------------------------\n");
    printf("\nlower triangle: \n");
    printm(lower, dim);

    printf("\n rhs: \n");
    printv(rhs, dim);

    free(coefs); free(permutation); free(rhs);
    mfree(lower, dim); mfree(upper, dim);

    return 0;
}


