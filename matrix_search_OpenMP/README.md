## Purpose
Parallelization using OpenMP.
The algorithm searches for a number which the user inputs, returning the number of occurences for the number.

## Approach
- The matrix A is initialized as: `A[i][j] = (2*i – j )%1000`
- 4 threads are used, with the command `omp_set_num_threads(4)`.