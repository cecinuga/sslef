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
void pivoting(double **A, size_t *permutation, const size_t dim){
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
void elimination(double **A, double **U, double **L, const size_t dim){
    /* Copy all rows of coefs (post-pivoting) into U before factoring */
    mcopy(U, A, dim);
    
    double elCoef = 0;
    for(size_t k = 0; k < dim; k++){
        for(size_t i = k+1; i < dim; i++){
            elCoef = U[i][k]/U[k][k];  
            L[i][k] = elCoef;

            for(size_t j = k; j < dim; j++){
                U[i][j] -= U[k][j]*elCoef; 
            }
        }
    }
}

void forward_sub(double **L, double *rhs, double *y, const size_t dim){
    for(size_t i = 0; i < dim; i++){
        y[i] = rhs[i];
        for(size_t j = 0; j < i; j++){
            y[i] -= L[i][j] * y[j];
        }
    }
}

void backward_sub(double **U, double *rhs, double *x, const size_t dim){
    for (size_t i = dim; i-- > 0;) {
        x[i] = rhs[i];       

        for (size_t j = i+1; j < dim; j++) {
            x[i] -= U[i][j] * x[j];         
        }
        x[i] /= U[i][i];                     
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
    double *fsrhs = calloc(dim, sizeof(double));
    double *sol = calloc(dim, sizeof(double));

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

    printf("\n------------------ORIGINAL-------------------\n");
    printf("\nA: \n");
    printm(coefs, dim);

    printf("\nrhs: \n");
    printv(rhs, dim);


    // -- PARTIAL PIVOTING ---
    printf("\n------------PARTIAL PIVOTING------------------\n");
    pivoting(coefs, permutation, dim);
    
    printf("\npermutation flatted matrix: \n");
    printv(permutation, dim);
    
    printf("\nA: \n");    
    printm(coefs, dim);

    printf("\nrhs: \n");
    printv(rhs, dim);

    // -- ELIMINATION ---

    printf("\n-----------------ELIMINATION--------------------\n");
    elimination(coefs, upper, lower, dim);
    
    printf("\nupper triangle: \n");
    printm(upper, dim);

    printf("\nlower triangle: \n");
    printm(lower, dim);

    printf("\n--------------FORWARD SUBSTITUTION-------------\n");
    perm(rhs, permutation, dim);
    forward_sub(lower, rhs, fsrhs, dim);

    printf("\nLy = Pb:\n");
    printv(fsrhs, dim);

    printf("\n--------------BACKWARD SUBSTITUTION-------------\n");
    backward_sub(upper, fsrhs, sol, dim);

    printf("\nUx = y\n");
    printv(sol, dim);

    free(coefs); free(permutation); free(rhs); free(fsrhs); free(sol);
    mfree(lower, dim); mfree(upper, dim);
 
    return 0;
}


