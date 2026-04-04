#ifndef LINALG_H
#define LINALG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Absolute value for doubles */
double dabs(double a);

/* Swap two elements in an integer vector */
void swap_vect(size_t *v, size_t dim, size_t i, size_t j);

/* Set all elements of a square matrix to zero */
void zeros(double **A, size_t dim);

/* Set the diagonal of a square matrix to one (identity) */
void eye(double **A, size_t dim);

/* Swap two rows of a square matrix */
void swap_row(double **A, size_t dim, size_t i, size_t j);

/* Apply permutation matrix to another matrix, the permutation matrix must be flatted. */
void perm_matrix(double **A, size_t *perm, const size_t dim);

/* Apply permutation matrix to a vector, the permutation matrix must be flatted. */
void perm_vect(size_t *v, size_t *perm, const size_t length);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_H */

