#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/// pass from 2D point to 1D point, used to calculate the position in 1D matrix notations
int to_line(int x, int y, int rows){
    return 2*x + y;
}

double get(double *A, int rank, int i, int j){
    assert(A != NULL);
    int pos = to_line(i, j, rank);

    assert(pos >= 0);
    assert(pos < rank*rank);
     
    return A[pos];
}

void set(double *A, int rank, int i, int j, int val){
    assert(A != NULL);

    int pos = to_line(i, j, rank);
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

double *factorize(const double *A, double *Lower, double *Upper, int rank){
    identity(rank, Lower);
    memcpy(Upper, A, sizeof(double)*rank*rank);
    
    return NULL;
}

/// @brief 
/// @param A The Matrix
/// @param n square rank
/// @return 
double *solve(double *Lower, double *Upper, double *consts, int rank){

    
    return NULL;
}

int main(void) {
    // DECLARE
    int rank = 2;
    size_t vector_size = sizeof(double)*rank;
    size_t matrix_size = sizeof(double)*rank*rank;
    
    double *A = malloc(matrix_size);
    double *Lower = malloc(matrix_size);
    double *Upper = malloc(matrix_size);
    double *consts = malloc(vector_size);

    // ASSIGN
    A[0] = 1; A[1] = 2; A[2] = 3; A[3] = 4;
    print_matrix(A, rank);

    factorize(A, Lower, Upper, rank);
    
    solve(Lower, Upper, consts, rank);

    free(A); free(Lower); free(Upper); free(consts);
}