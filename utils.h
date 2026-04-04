#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Allocate a row x col double matrix via calloc (all entries start at 0.0).
 * The outer pointer array is NULL-checked; inner row callocs are not. */
double **mmalloc(size_t row, size_t col);
double *vmalloc(const size_t length);

/* Free each row array then the outer pointer array.
 * Do NOT call on matrices whose row pointers point to stack memory. */
void mfree(double **A, size_t row);

void mcopy(double **dest, double **src, const size_t dim);

/* Type-specific print implementations */
void printv_sz (size_t *v, size_t dim);
void printv_int(int    *v, size_t dim);
void printv_dbl(double *v, size_t dim);

void printm_dbl(double **A, size_t dim);
void printm_int(int    **A, size_t dim);

/* Generic print macros — work with size_t*, int*, double* vectors
 * and double**, int** matrices. */
#define printv(v, dim) _Generic((v),  \
    size_t*: printv_sz,               \
    int*:    printv_int,              \
    double*: printv_dbl               \
)(v, dim)

#define printm(A, dim) _Generic((A),  \
    double**: printm_dbl,             \
    int**:    printm_int              \
)(A, dim)

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */
