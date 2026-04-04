/*
 * utils.c -- Console print helpers for debugging.
 */

#include <stdio.h>
#include <stdlib.h>

/* Allocate a row x col double matrix via calloc (all entries start at 0.0).
 * The outer pointer array is NULL-checked; inner row callocs are not. */
double **matrix_alloc(const size_t row, const size_t col){
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

/* Free each row array then the outer pointer array.
 * Do NOT call on matrices whose row pointers point to stack memory. */
void matrix_free(double **A, const size_t row){
    for (size_t i = 0; i < row; i++) {
        free(A[i]);
    }
    free(A);
}

void matrix_copy(double **dest, double **src, const size_t dim){
    for (size_t i = 0; i < dim; i++)
        for(size_t j = 0; j < dim; j++)
            dest[i][j] = src[i][j];
}

void print_stvector(size_t *v, size_t dim){
    printf("[");
    for(size_t i = 0; i < dim; i++){
        printf("%lu", v[i]);
        if(i < dim-1) printf(",");
    }
    printf("]\n");
}

/* Print a dim x dim double matrix in nested-bracket notation.
 * Assumes a square matrix; a separate column count is not supported. */
void print_matrix(double **A, size_t dim){
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
