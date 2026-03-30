#include <stdlib.h>
#include <stdio.h>

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
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

void swap_row(double **A, const int rank, const int i, const int j){
    double *tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

int *partial_pivoting(double **A, int *permutation, const int rank){
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

void elimination(double **coefs, double **U, double **L, int rank){
    for(int j = 0; j < rank; j++)
        U[0][j] = coefs[0][j];

    
}

int main(void) {
    int rank = 3;

    int *permutation = calloc(rank, sizeof(int));
    double **coefs = calloc(rank, sizeof(double)*rank);
    double **upper = calloc(rank, sizeof(double)*rank); // FIX MEMORY LEAK ACCESSING TO NULL POSITION
    double **lower = calloc(rank, sizeof(double)*rank);

    double *consts = calloc(rank, sizeof(double));

    double col0[] = {1, 2, 5, 6, -4}; 
    double col1[] = {3, 8, 10, -3, -8}; 
    double col2[] = {0, -4, 3, -4, }; 
    double col3[] = {-5, 4, 1.36, 7.89, -9.69}; 
    double col4[] = {0, -7, 2, 12, -1.5}; 

    coefs[0] = (double*)&col0;
    coefs[1] = (double*)&col1;
    coefs[2] = (double*)&col2;
    coefs[3] = (double*)&col3;
    coefs[4] = (double*)&col4;


    printf("original matrix: \n");
    print_matrix(coefs, rank);

    printf("\nafter partial pivoting: \n");
    partial_pivoting(coefs, permutation, rank);
    print_matrix(coefs, rank);
    
    printf("\npermutation flatted matrix: \n");
    print_ivector(permutation, rank);

    /*elimination(coefs, upper, lower, rank);

    printf("------------------------------\n");
    printf("after elimination: \n");
    print_matrix(coefs, rank);
    
    printf("\nupper triangle: \n");
    print_matrix(upper, rank);*/

    free(permutation); free(coefs); free(consts); free(upper); free(lower);
}