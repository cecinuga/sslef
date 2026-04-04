# sslef — Solve System of Linear Equations via Factorization

A C implementation of LU (lower-upper) matrix factorization for solving square
systems of linear equations **Ax = b**.

---

## Project structure

```
.
├── solver.c     # Entry point: pivoting(), elimination(), main()
├── linalg.c     # Matrix/vector primitives (swaps, init, multiply)
├── linalg.h
├── utils.c      # Alloc, free, copy, print helpers
├── utils.h      # Generic printv/printm macros
└── Makefile
```

---

## Build

```bash
make          # compiles to build/solver and creates a ./solver symlink
make clean    # removes build/ and the symlink
```

Requires GCC. Flags: `-Wall -Wextra -g`.

---

## Algorithm

Goal: **PA = LU** decomposition of an n×n matrix A.

| Symbol | Meaning |
|--------|---------|
| **P**  | Permutation matrix (row swaps from partial pivoting) |
| **L**  | Unit lower-triangular (diagonal = 1, Doolittle form) |
| **U**  | Upper-triangular matrix |

Once L and U are known, **Ax = b** is solved in two steps:
1. **Forward substitution** — solve **Ly = Pb** for y
2. **Back substitution**   — solve **Ux = y** for x

Steps 1 and 2 are not yet implemented.

---

## Functions

#### `pivoting(A, permutation, dim)` — [solver.c](solver.c)
For each column k, finds row j ≥ k with maximum `|A[j][k]|` and swaps it to
position k. Records swaps in `permutation[]`.

#### `elimination(A, U, L, dim)` — [solver.c](solver.c)
Doolittle LU factorization. Copies A into U first, then for each pivot column k:
`L[i][k] = U[i][k] / U[k][k]` and `U[i][j] -= L[i][k] * U[k][j]`.

#### `dabs(a)` — [linalg.c](linalg.c)
Absolute value of a `double`; avoids the `<math.h>` / `-lm` dependency.

#### `swap(v, dim, i, j)` — [linalg.c](linalg.c)
Swaps `v[i]` and `v[j]` in a `size_t` array (keeps permutation vector in sync).

#### `swapr(A, dim, i, j)` — [linalg.c](linalg.c)
Exchanges row pointers `A[i]` and `A[j]` in O(1).

#### `permm(A, perm, dim)` — [linalg.c](linalg.c)
Applies a flattened permutation vector to a matrix by swapping rows.

#### `permv(v, perm, length)` — [linalg.c](linalg.c)
Applies a flattened permutation vector to another vector.

#### `zeros(A, dim)` / `eye(A, dim)` — [linalg.c](linalg.c)
`zeros` fills every entry with 0.0; `eye` sets the main diagonal to 1.0.

#### `mmmul(A, B, out, dim)` — [linalg.c](linalg.c)
Square matrix × matrix multiplication. Accumulates into scalar `c` before
writing; **not aliasing-safe** — `out == A` corrupts same-row reads, `out == B`
corrupts same-column reads across rows.

#### `mcmul(A, v, out, dim)` — [linalg.c](linalg.c)
Matrix × column vector multiplication. Uses an internal buffer to allow
`out == v` (aliasing-safe).

#### `mmalloc(row, col)` / `mfree(A, row)` — [utils.c](utils.c)
Heap-allocates / frees a `row×col` `double**` matrix via `calloc`.

#### `vtmalloc(length)` — [utils.c](utils.c)
Heap-allocates a `double*` vector via `calloc`.

#### `mcopy(dest, src, dim)` — [utils.c](utils.c)
Element-wise copy of a square matrix.

#### `printv(v, dim)` / `printm(A, dim)` — [utils.h](utils.h)
Generic `_Generic` macros dispatching to type-specific implementations
(`printv_sz`, `printv_int`, `printv_dbl`, `printm_dbl`, `printm_int`) in
[utils.c](utils.c). Print in bracket notation.

---

## Current limitations

- No forward or back substitution; **the system is factored but not solved**.
- The test matrix and RHS vector are hard-coded; no runtime input supported.

---

## TODO

### 0. Immediate fixes
- [ ] Fix aliasing bug in `mmmul` when `out == A` or `out == B`

### 1. Code quality
- [ ] Accept system input at runtime (stdin or file) instead of hard-coded arrays.

### 2. Missing solver pipeline

- [ ] **Develop test suite** — unit tests for solver functions.
- [ ] **Forward substitution** `forward_sub(L, b, y, dim)` — solve `Ly = Pb`.
- [ ] **Back substitution** `back_sub(U, y, x, dim)` — solve `Ux = y`.
- [ ] **Near-zero pivot guard** — return error if `|U[k][k]| < eps` (singular matrix).
- [ ] **Residual check** — compute `||Ax - b||` after solving.
- [ ] **`solve(A, b, x, dim)`** — orchestrate the full pipeline.

### 3. Longer-term improvements
- [ ] Scaled partial pivoting or complete pivoting for better numerical stability.
- [ ] Flat `double*` + stride layout instead of `double**` for cache locality.
- [ ] Iterative refinement to improve floating-point accuracy.
