## Purpose
Parallelization using OpenMP.
In the code under this folder, the elements of a matrix are summed.

## Approach
- The matrix A is initialized as: `A[i][j] = (3*i-j)/2)`
- 8 threads are used, with the command `omp_set_num_threads(8)`.