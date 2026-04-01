#ifndef LINALG_H
#define LINALG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Absolute value for doubles */
double dabs(double a);

/* Swap two elements in an integer vector */
void swap_vect(int *v, size_t rank, size_t i, size_t j);

/* Set all elements of a square matrix to zero */
void zeros(double **A, size_t rank);

/* Set the diagonal of a square matrix to one (identity) */
void eye(double **A, size_t rank);

/* Swap two rows of a square matrix */
void swap_row(double **A, size_t rank, size_t i, size_t j);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_H */
