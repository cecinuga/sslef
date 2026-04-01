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
void eye(double **A, int rank);

/* Swap two rows of a square matrix */
void swap_row(double **A, int rank, int i, int j);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_H */
