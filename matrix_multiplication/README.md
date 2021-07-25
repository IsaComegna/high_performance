## Purpose
Parallelize the multiplication of square matrixes `n x n` of a varied number, informed by the user. In this folder, two files can be found: one using processes and the other using threads.

## Specification
Input: parameter `n` used to determine the size of the square matrices `n x n` A and B.
The code outputs the result C, being `A x B = C`.
The matrices are initialised as follows:
- For A:  `Aij = i + j`;
- For B: `Bij = i - j`;
- C is initialized with empty fields.

## Parallelization with processes
The code was paralellized with 4 processes:
- The code was divided into two logical parts. The first part is the one that initializes the code and generates other 3 processes.
- Each process is responsible for initializing 1/4 of the matrices A, B and C. Each process is responsible for `n/4` lines of each of the matrices.
- After the matrices are initialized, the processes created from the first process are halted. The memmory space occupied by them is freed (no longer associated to the processes).
- After that, other 3 processes are created from the remaining one and the multiplication between A and B is started.
- Each process (of the total 4) is responsible for computing `n/4` lines of the C matrix. In order to do so, each process is responsible for accessing `n/4` lines of the matrix A and and columns from B. This way, there's no precedence issue when writting the results in C.
- The algorithm used is:
```C = ΣiΣjΣk(Ai,k x Bk,j)```

translated to C as:
```
for (int i = start; i < end; i++) 
        for (int j = 0; j < n; j++) 
            for (int k = 0; k < n; k++) 
                C[i][j] += A[i][k] * B[k][j];

```

### Time complexity
The sequential code has a time complexity of O(n) = n^3. With this parallelization, the time complexity is reduced to: O(n) = n^2/sqrt(p), with p representing the number of processes (in this case, 4).

### Execution time
With the help of a time library, the execution times for the sequential and the parallel codes can be viewed below:

n = 4:
Multi-processes
- Matrices initialization: 0.0011080s
- Multiplication: 0.0005260s
Sequential:
- Matrices initialization: 0.0004370s
- Multiplication:  0.0000010s

n = 1000:
Multi-processes
- Matrices initialization: 0.0096770s
- Multiplication: 2.2072300s
Sequential:
- Matrices initialization: 0.0209600s
- Multiplication:  6.4175200s

The difference in computing time between the two approches was bigger then 50%, depending on n.
For smaller n, the parallelization is not very efficient, because of the concurrency in memory accesses.



## Parallelization with threads
The approach is very similar to the processes one, but, instead of instantiating 4 processes, 4 threads are used.

### Execution time
With the help of a time library, the execution times for the sequential and the parallel codes can be viewed below:

n = 4:
Multi-threads
- Matrices initialization: 0.0007800s
- Multiplication: 0.0004700s
Sequential:
- Matrices initialization: 0.0004370s
- Multiplication:  0.0000010s

n = 1000:
Multi-threads
- Matrices initialization: 0.0070660 
- Multiplication: 1.7423410s
Sequential:
- Matrices initialization: 0.0209600s
- Multiplication:  6.4175200s

