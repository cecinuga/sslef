#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Print an integer vector */
void print_ivector(int *v, int rank);

/* Print a square matrix */
void print_matrix(double **A, int rank);

void matrix_copy(double **dest, double **src, const int rank);

/* Allocate a row x col matrix; caller must free with matrix_free() */
double **matrix_alloc(int row, int col);

/* Free a matrix allocated by matrix_alloc() */
void matrix_free(double **A, int row);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */
