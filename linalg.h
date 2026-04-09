#ifndef LINALG_H
#define LINALG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Absolute value for doubles */
double dabs(double a);

/* Swap two elements in an size_t vector */
void swapvst(size_t *v, const size_t dim, const size_t i, const size_t j);

/* Swap two elements in an doible vector */
void swapv(double *v, const size_t dim, const size_t i, const size_t j);

/* Swap two rows of a square matrix */
void swapr(double **A, const size_t dim, const size_t i, const size_t j);

#define swap(v, dim, i, j) _Generic((v),  \
    size_t*: swapvst,               \
    double*: swapv,              \
    double**: swapr               \
)(v, dim, i, j)

/* Apply permutation matrix to a double matrix, the permutation matrix must be flatted. */
void permm(double **A, size_t *perm, const size_t dim);

/* Apply permutation matrix to a double vector, the permutation matrix must be flatted. */
void permv(double *v, size_t *perm, const size_t length);

/* Apply permutation matrix to a size_t vector, the permutation matrix must be flatted. */
void permvst(size_t *v, size_t *perm, const size_t length);

#define perm(m, perms, dim) _Generic((m),  \
    size_t*: permvst,               \
    double*: permv,              \
    double**: permm               \
)(m, perms, dim)

/* Set all elements of a square matrix to zero */
void zeros(double **A, const size_t dim);

/* Set the diagonal of a square matrix to one (identity) */
void eye(double **A, const size_t dim);

/* Perform matrix by matrix multiplication (only square matrix) */
void mmmul(double **A, double **B, double **out, const size_t dim);

/* Perform matrix by column multiplication (only square matrix) */
void mcmul(double **A, double *v, double *out, const size_t dim);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_H */

