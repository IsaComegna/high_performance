#include <stdio.h>
#include <omp.h>


int main()
{
  int i, j;
  int A[1000][1000];
  int elemento=0;
  int numero_ocorrencias = 0;
  int total = 0;

  printf("Valor do elemento buscado (numero inteiro): ");
  scanf("%d",&elemento);

  omp_set_num_threads(4);
  #pragma omp parallel private(i, j)
  {
    #pragma omp for
      for(i = 0; i < 1000; i++){
        for (j = 0; j < 1000; j++){
          A[i][j] = (2*i-j)%1000;
        }
      }

    #pragma omp for reduction(+:numero_ocorrencias)
      for (i = 0; i < 1000; i++){
        for (j = 0; j < 1000; j++){
          if (A[i][j] == elemento){
            numero_ocorrencias = numero_ocorrencias + 1;
          }
        }
      }
  }

  printf("\nNumero de ocorrencias final = %d\n",numero_ocorrencias);
  fflush(stdout);
}