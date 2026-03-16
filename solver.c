#include <stdlib.h>
#include <stdio.h>

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

void elimination(double **coefs, double **U, double **L, int rank){
    for(int j = 0; j < rank; j++)
        U[0][j] = coefs[0][j];

    for(int i = 1; i < rank; i++){
        double c = 0;
        int firstNonZero = 0;
        for(int j = 0; j < rank; j++){
            U[i][j] = coefs[i][j]; // FIX MEMORY LEAK ACCESSING TO NULL POSITION
            if (!firstNonZero && coefs[i][j] != 0){
                c = coefs[i][j]/coefs[i-1][j];
                firstNonZero = 1;
            }
            //U[i][j] -= coefs[i-1][j] * c;
            
            // FOUND PIVOT AND ASSIGN TO L[i][j]
        }
    }
}

int main(void) {
    int rank = 3;

    double **coefs = calloc(rank, sizeof(double)*rank);
    double **upper = calloc(rank, sizeof(double)*rank); // FIX MEMORY LEAK ACCESSING TO NULL POSITION
    double **lower = calloc(rank, sizeof(double)*rank);

    double *consts = calloc(rank, sizeof(double));

    double col1[] = {1, 2, 1}; 
    double col2[] = {3, 8, 1}; 
    double col3[] = {0, 4, 1}; 

    coefs[0] = (double*)&col1;
    coefs[1] = (double*)&col2;
    coefs[2] = (double*)&col3;


    printf("before elimination: \n");
    print_matrix(coefs, rank);
    
    elimination(coefs, upper, lower, rank);

    printf("------------------------------\n");
    printf("after elimination: \n");
    print_matrix(coefs, rank);
    
    printf("\nupper triangle: \n");
    print_matrix(upper, rank);

    free(coefs); free(consts); free(upper); free(lower);
}