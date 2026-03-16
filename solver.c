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

void elimination(double **coefs, int rank){
    for(int i = 1; i < rank; i++){
        double c = 0;
        for(int j = 0; j < rank; j++){
            if(j < i && coefs[i][j] != 0) { // perform elimination 
                c = coefs[i][j]/coefs[i-1][j];
            }
            coefs[i][j] -= coefs[i-1][j] * c;
        }
    }
}


int main(void) {
    // DECLARE
    int rank = 3;

    double **coefs = calloc(rank, sizeof(double)*rank);
    double *consts = calloc(rank, sizeof(double));

    double col1[] = {1, 2, 1}; 
    double col2[] = {3, 8, 1}; 
    double col3[] = {0, 4, 1}; 

    coefs[0] = (double*)&col1;
    coefs[1] = (double*)&col2;
    coefs[2] = (double*)&col3;


    printf("before elimination: \n");
    print_matrix(coefs, rank);
    
    elimination(coefs, rank);

    printf("------------------------------\n");
    printf("after elimination: \n");
    print_matrix(coefs, rank);

    free(coefs); free(consts);
}