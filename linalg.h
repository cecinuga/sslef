#ifndef LINALG_H
#define LINALG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Absolute value for doubles */
double dabs(double a);

/* Swap two elements in an integer vector */
void swapi(int *v, int rank, int i, int j);

/* Set all elements of a square matrix to zero */
void zeros(double **A, int rank);

/* Set the diagonal of a square matrix to one (identity) */
void ones(double **A, int rank);

/* Allocate a row x col matrix; caller must free with matrix_free() */
double **matrix_alloc(int row, int col);

/* Free a matrix allocated by matrix_alloc() */
void matrix_free(double **A, int row);

/* Swap two rows of a square matrix */
void swap_row(double **A, int rank, int i, int j);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_H */
