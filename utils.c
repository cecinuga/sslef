/*
 * utils.c -- Console print helpers for debugging.
 */

#include <stdio.h>

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
