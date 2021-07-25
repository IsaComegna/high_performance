#include <stdio.h>
#include <omp.h>


int main()
{
  int i, j;
  double A[1000][1000];
  double soma = 0.0;

  omp_set_num_threads(8);
  #pragma omp parallel private(i, j) reduction(+:soma)
  {
    #pragma omp for
      for(i = 0; i < 1000; i++){
        for (j = 0; j < 1000; j++){
          A[i][j] = (3*i-j)/2;
        }
      }

    #pragma omp for
      for (i = 0; i < 1000; i++){
        for (j = 0; j < 1000; j++){
          soma = soma + A[i][j];
        }
      }
  }
  printf("SOMA TOTAL = %f\n",soma);
}