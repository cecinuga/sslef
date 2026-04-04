/*
 * utils.c -- Console print helpers for debugging.
 */

#include <stdio.h>
#include <stdlib.h>

double **mmalloc(const size_t row, const size_t col){
    double **A = calloc(row, sizeof(double*));
    if(A == NULL)
        perror("[!] no more memory allocating matrix");

    for (size_t i = 0; i < row; i++) {
        A[i] = calloc(col, sizeof(double));
        if(A[i] == NULL)
            perror("[!] no more memory allocating matrix");
    }

    return A;
}

double *vtmalloc(const size_t length){
    double *v = calloc(length, sizeof(double));
    if(v == NULL)
        perror("[!] no more memory allocating matrix");

    return v;
}

void mfree(double **A, const size_t row){
    for (size_t i = 0; i < row; i++) {
        free(A[i]);
    }
    free(A);
}

void mcopy(double **dest, double **src, const size_t dim){
    for (size_t i = 0; i < dim; i++)
        for(size_t j = 0; j < dim; j++)
            dest[i][j] = src[i][j];
}

/* --- printv --- */

void printv_sz(size_t *v, size_t dim){
    printf("[");
    for(size_t i = 0; i < dim; i++){
        printf("%zu", v[i]);
        if(i < dim-1) printf(",");
    }
    printf("]\n");
}

void printv_int(int *v, size_t dim){
    printf("[");
    for(size_t i = 0; i < dim; i++){
        printf("%d", v[i]);
        if(i < dim-1) printf(",");
    }
    printf("]\n");
}

void printv_dbl(double *v, size_t dim){
    printf("[");
    for(size_t i = 0; i < dim; i++){
        printf("%lf", v[i]);
        if(i < dim-1) printf(",");
    }
    printf("]\n");
}

/* --- printm --- */

void printm_dbl(double **A, size_t dim){
    printf("[");
    for(size_t i = 0; i < dim; i++){
        if(i>0) printf(" ");
        printf("[ ");
        for(size_t j = 0; j < dim; j++) printf("%lf ", A[i][j]);
        printf("]");
        if(i < dim-1) printf(",\n");
    }
    printf("]\n");
}

void printm_int(int **A, size_t dim){
    printf("[");
    for(size_t i = 0; i < dim; i++){
        if(i>0) printf(" ");
        printf("[ ");
        for(size_t j = 0; j < dim; j++) printf("%d ", A[i][j]);
        printf("]");
        if(i < dim-1) printf(",\n");
    }
    printf("]\n");
}
