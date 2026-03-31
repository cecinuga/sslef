#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Print an integer vector */
void print_ivector(int *v, int rank);

/* Print a square matrix */
void print_matrix(double **A, int rank);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */
