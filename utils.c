#include "utils.h"

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
