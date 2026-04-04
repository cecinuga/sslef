/*
 * linalg.c -- Low-level matrix primitives: alloc/free, initialization, swaps.
 *
 * All matrices are represented as double** (array of row pointers).
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

double dabs(double a){
    if (a >= 0) return a;
    return a*-1;
}

void swap(size_t *v, const size_t dim, const size_t i, const size_t j){
    assert(i < dim);
    assert(j < dim);

    size_t tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void swapr(double **A, const size_t dim, const size_t i, const size_t j){
    assert(i < dim);
    assert(j < dim);

    double *tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void permm(double **A, size_t *perm, const size_t dim){
    for(size_t i = 0; i < dim; i++)
        swapr(A, dim, i, perm[i]);
}

void permv(size_t *v, size_t *perm, const size_t length){
    for(size_t i = 0; i < length; i++)
        swap(v, length, i, perm[i]);
}

void zeros(double **A, const size_t dim){
    for(size_t i = 0; i < dim; i++){
        for(size_t j = 0; j < dim; j++){
            A[i][j] = 0;
        }
    }
}

void eye(double **A, const size_t dim){
    for(size_t i = 0; i < dim; i++)
        for(size_t j = 0; j < dim; j++)
            A[i][j] = (i == j) ? 1.0 : 0.0;
}

void mmmul(double **A, double **B, double **out, const size_t dim){
    double c = 0;
    for(size_t i = 0; i < dim; i++){
        for(size_t j = 0; j < dim; j++){
            c = 0;
            for(size_t k = 0; k < dim; k++){
                c += A[i][k] * B[k][j];
            }
            out[i][j] = c;
        }
    }
}

void mcmul(double **A, double *v, double *out, const size_t dim){
    double *buf = vmalloc(dim);
    for(size_t i = 0; i < dim; i++){
        c = 0;
        for(size_t j = 0; j < dim; j++){
            c += A[i][j] * v[j];
        }
        out[i] = c;
    }
}