/*
 * utils.c -- Console print helpers for debugging.
 */

#include <stdio.h>
#include <stdlib.h>

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

void matrix_copy(double **dest, double **src, const int rank){
    for (int i = 0; i < rank; i++)
        for(int j = 0; j < rank; j++)
            dest[i][j] = src[i][j];
}

/* Print an integer array of length rank as [a,b,c,...]. */
void print_ivector(int *v, int rank){
    printf("[");
    for(int i = 0; i < rank; i++){
        printf("%d", v[i]);
        if(i < rank-1)
            printf(",");
    }
    printf("]\n");
}

/* Print a rank x rank double matrix in nested-bracket notation.
 * Assumes a square matrix; a separate column count is not supported. */
void print_matrix(double **A, int rank){
    printf("[");
    for(int i = 0; i < rank; i++){
        if(i>0) printf(" ");
        printf("[ ");
        for(int j = 0; j < rank; j++){
            printf("%lf ", A[i][j]);
        }
        printf("]");
        if(i < rank-1) printf(",\n");
    }
    printf("]\n");
}
