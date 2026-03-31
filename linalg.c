#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linalg.h"

double dabs(double a){
    if (a >= 0) return a;
    return a*-1;
}

void swapi(int *v, const int rank, const int i, const int j){
    assert(i < rank);
    assert(j < rank);

    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void zeros(double **A, const int rank){
    for(int i = 0; i < rank; i++){
        for(int j = 0; j < rank; j++){
            A[i][j] = 0;
        }
    }
}

void ones(double **A, const int rank){
    for(int i = 0; i < rank; i++){
        A[i][i] = 1;
    }
}

double **matrix_alloc(const int row, const int col){
    double **A = calloc(row, sizeof(double*));
    if(A == NULL)
        perror("[!] no more memory");
    
    for (int i = 0; i < row; i++) {
        A[i] = calloc(col, sizeof(double));
    }

    return A;
}

void *matrix_free(double **A, const int row){
    for (int i = 0; i < row; i++) { 
        free(A[i]);
    }
    free(A);
}

void swap_row(double **A, const int rank, const int i, const int j){
    assert(i < rank);
    assert(j < rank);

    double *tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
