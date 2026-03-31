#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void print_ivector(int *v, int rank){
    printf("[");
    for(int i = 0; i < rank; i++){
        printf("%d", v[i]);
        if(i < rank-1) 
            printf(",");
    }
    printf("]\n");
}

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

void partial_pivoting(double **A, int *permutation, const int rank){
    int max_i = 0;
    double max = 0;

    for (int i = 0; i < rank; i++ )
        permutation[i] = i;

    for (int i = 0; i < rank; i++){
        max_i = i;
        max = A[i][i];
        for (int j = i; j < rank; j++){
            if ( dabs(A[j][i]) > max ) {
                max_i = j;
                max = dabs(A[j][i]);
            }
        }

        swapi(permutation, rank, i, max_i);
        swap_row(A, rank, i, max_i);
    }
}

/// @brief Perform factorized elimination on coefs
/// @param coefs must be pre-allocated and pre-inizialized
/// @param U must be pre-allocated and pre-inizialized
/// @param L must be pre-allocated and pre-inizialized
/// @param rank 
void elimination(double **coefs, double **U, double **L, const int rank){
    for(int i = 0; i < rank; i++)
        U[0][i] = coefs[0][i];

    double elCoef = 0;
    for(int k = 0; k < rank; k++){
        for(int i = k+1; i < rank; i++){
            elCoef = coefs[i][k]/coefs[i-1][k];
            L[i][k] = elCoef;
            for(int j = i-1; j < rank; j++){
                //printf("(%d, %d, %d)", i, j, k);
                U[i][j] = coefs[i][j]-(coefs[i-1][j]*elCoef);
            }
        }
    }
}

int main(void) {
    const int rank = 4;

    int *permutation = calloc(rank, sizeof(int));
    double **coefs = calloc(5, sizeof(double*));
    double **upper = matrix_alloc(rank, rank);
    double **lower = matrix_alloc(rank, rank);
    double *consts = calloc(rank, sizeof(double));

    double col0[] = {1, 2, 5, 6, -4}; 
    double col1[] = {3, 8, 10, -3, -8}; 
    double col2[] = {2, -4, 3, -4, }; 
    double col3[] = {-5, 4, 1.36, 7.89, -9.69}; 
    double col4[] = {1, -7, 2, 12, -1.5}; 

    coefs[0] = (double*)&col0;
    coefs[1] = (double*)&col1;
    coefs[2] = (double*)&col2;
    coefs[3] = (double*)&col3;
    coefs[4] = (double*)&col4;

    zeros(upper, rank);
    ones(lower, rank);

    printf("original matrix: \n");
    print_matrix(coefs, rank);

    printf("\nafter partial pivoting: \n");
    partial_pivoting(coefs, permutation, rank);
    print_matrix(coefs, rank);
    
    printf("\npermutation flatted matrix: \n");
    print_ivector(permutation, rank);

    elimination(coefs, upper, lower, rank);

    printf("------------------------------\n");
    printf("\nupper triangle: \n");
    print_matrix(upper, rank);

    printf("------------------------------\n");
    printf("\nlower triangle: \n");
    print_matrix(lower, rank);

    matrix_free(lower, rank); matrix_free(upper, rank);
    free(permutation); free(coefs); free(consts); 
}