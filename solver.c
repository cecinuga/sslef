#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/// pass from 2D point to 1D point, used to calculate the position in 1D matrix notations
int to_line(int i, int j){
    return (i+1)*(j+1)-1;
}

double get(double *A, int rank, int i, int j){
    assert(A != NULL);

    int pos = to_line(i, j);
    assert(pos < rank*rank);
     
    return A[pos];
}

void set(double *A, int rank, int i, int j, int val){
    assert(A != NULL);

    int pos = to_line(i, j);
    assert(pos < rank*rank);

    A[pos] = val;
}

void print_matrix(double *A, int rank){
    printf("[");
    for(int i = 0; i < rank; i++){
        if(i>0) printf(" ");
        printf("[ ");
        for(int j = 0; j < rank; j++){
            printf("%lf ", get(A, rank, i, j));
        }
        printf("]");
        if(i < rank-1) printf(",\n");
    }
    printf("]\n");
}

/// @brief perform this operation to out: 
/// if i=j assign 1 at (i,j), 0 otherwise
/// @param n 
/// @param out 
void identity(int rank, double *out){
    for(int i = 0; i < rank; i++){
        set(out, rank, i, i, 1);
    }
}

double *factorize(double *A, int rank, double *Lower, double *Upper){
    identity(rank, Lower);
    identity(rank, Upper);
    
}

/// @brief 
/// @param A The Matrix
/// @param n square rank
/// @return 
double *solver(double *A, int rank){

    
    return NULL;
}

int main(void) {
    int rank = 3;
    size_t size = sizeof(double)*rank*rank;
    
    double *A = malloc(size);
    double *Lower = malloc(size);
    double *Upper = malloc(size);

    factorize(A, rank, Lower, Upper);
    
    print_matrix(A, rank);

    solver(NULL, 3);

    free(A); free(Lower); free(Upper);
}