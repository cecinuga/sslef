#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Print an size_t vector */
void print_stvector(size_t *v, size_t dim);

/* Print a square matrix */
void print_matrix(double **A, size_t dim);

void matrix_copy(double **dest, double **src, const size_t dim);

/* Allocate a row x col matrix; caller must free with matrix_free() */
double **matrix_alloc(size_t row, size_t col);

/* Free a matrix allocated by matrix_alloc() */
void matrix_free(double **A, size_t row);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */
