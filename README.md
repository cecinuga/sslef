# sslef — Solve System of Linear Equations via Factorization

A C implementation of LU (lower-upper) matrix factorization for solving square
systems of linear equations **Ax = b**.  The factorization step works correctly
after partial pivoting; forward/back substitution is not yet implemented.

---

## Project structure

```
.
├── solver.c     # Entry point: partial_pivoting(), elimination()
├── linalg.c     # Matrix/vector primitives (swap, init)
├── linalg.h
├── utils.c      # utils (alloc, free, printf)
├── utils.h
└── Makefile
```

---

## Build

```bash
make          # compiles to build/solver and creates a ./solver symlink
make clean    # removes build/ and the symlink
```

Requires GCC.  Flags: `-Wall -Wextra -g`.

---

## Algorithm

The goal is **PA = LU** decomposition of an n×n matrix A:

| Symbol | Meaning |
|--------|---------|
| **P**  | Permutation matrix encoding row swaps from partial pivoting |
| **L**  | Unit lower-triangular matrix (diagonal = 1, Doolittle form) |
| **U**  | Upper-triangular matrix |

Once L and U are known, **Ax = b** is solved in two steps:
1. **Forward substitution** — solve **Ly = Pb** for y
2. **Back substitution**   — solve **Ux = y** for x

Steps 1 and 2 are not yet implemented.

---

## Functions

#### `partial_pivoting(A, permutation, rank)` — [solver.c](solver.c)
For each column k, finds the row j ≥ k with maximum `|A[j][k]|` and swaps it
to the diagonal position.  Records swaps in `permutation[]` so the same
reordering can be applied to the RHS vector b.

#### `elimination(coefs, U, L, rank)` — [solver.c](solver.c)
Doolittle LU factorization.  For each pivot column k computes multipliers
`L[i][k] = coefs[i][k] / coefs[k][k]` and updates
`U[i][j] = coefs[i][j] - L[i][k] * coefs[k][j]`.
**Bug**: reads from original `coefs` at every step instead of the evolving U
(see TODO §2).

#### `dabs(a)` — [linalg.c](linalg.c)
Absolute value of a `double`; avoids the `<math.h>` / `-lm` dependency.

#### `swapi(v, rank, i, j)` — [linalg.c](linalg.c)
Swaps `v[i]` and `v[j]` in an integer array.  Keeps the permutation vector
in sync with `swap_row`.

#### `swap_row(A, rank, i, j)` — [linalg.c](linalg.c)
Exchanges row pointers `A[i]` and `A[j]` in O(1).

#### `zeros(A, rank)` / `ones(A, rank)` — [linalg.c](linalg.c)
`zeros` fills every entry with 0.0; `ones` sets the main diagonal to 1.0
(initialises L to the identity matrix).

#### `matrix_alloc(row, col)` / `matrix_free(A, row)` — [linalg.c](linalg.c)
Heap-allocates / frees a `row×col` `double**` matrix via `calloc`.

#### `print_matrix(A, rank)` / `print_ivector(v, rank)` — [utils.c](utils.c)
Print a square matrix or integer vector in bracket notation.

---

## Current limitations

- `elimination()` reads from the original `coefs` at every step; prior
  elimination results are not propagated, producing wrong L and U for k ≥ 1.
- No forward or back substitution; **the system is never solved**.
- `consts` (the RHS vector b) is allocated but never populated or used.
- The test matrix is hard-coded; no runtime input is supported.

---

## TODO

### 1. Code quality

- [ ] Remove or wire up `consts` — either delete the allocation or connect it
  to the forward substitution step once that is implemented.
- [ ] Remove the dead `//printf(...)` line inside `elimination()`.
- [ ] Rename `ones` to `set_identity` (or `eye`) — the name implies filling
  with 1s, not setting only the diagonal.
- [ ] Accept system input at runtime (stdin or file) instead of hard-coded arrays.

### 3. Missing solver pipeline

- [ ] **Apply permutation to b** before forward substitution — `partial_pivoting`
  reorders A rows but the same permutation must be applied to b.
- [ ] **Forward substitution** `forward_sub(L, b, y, rank)` — solve `Ly = Pb`
  exploiting the unit lower-triangular structure (no diagonal division needed).
- [ ] **Back substitution** `back_sub(U, y, x, rank)` — solve `Ux = y` from
  the last row upward.
- [ ] **Near-zero pivot guard** — if `|U[k][k]| < eps` after pivoting the
  matrix is singular; return an error code instead of dividing by near-zero.
- [ ] **Residual check** — after solving, compute `||Ax - b||` to report
  solution accuracy.

### 4. Longer-term improvements

- [ ] Consider a flat `double*` + stride layout instead of `double**` for
  better cache locality on large matrices.
- [ ] Add iterative refinement to improve floating-point accuracy.
