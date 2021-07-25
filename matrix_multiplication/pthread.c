#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define n_threads 3
int SIZE;

double a[2000][2000], b[2000][2000], c[2000][2000];
int n_iter;
pthread_t tid[n_threads];

void *inicia_matrizes(void *arg)
{
  int i, j, inicio, fim, id_thread;

  id_thread = *(int *)arg;
  inicio = (id_thread+1) * n_iter;
  fim = inicio + n_iter;

  for(i = inicio; i < fim; i++)
    for(j = 0; j < SIZE; j++){
      a[i][j] = i+j;
      b[i][j] = i-j;
      c[i][j] = (double)0.0;
   }
}

void *multiplica_matrizes(void *arg)
{
  int i, j, k, inicio, fim, id_thread;

  id_thread = *(int *)arg;
  inicio = (id_thread + 1) * n_iter;
  fim = inicio + n_iter;

  for(i = inicio; i < fim; i++){
    for(k = 0; k < SIZE; k++){
      for(j = 0; j < SIZE; j++){
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

void main(argc, argv)
int argc;
char **argv;
{
  int i, k, id_thread[n_threads];
  int p = -1;
  int inicio, fim;

  if (argc > 1){
    SIZE = atoi(argv[1]);
    printf("Matriz %dx%d\n",SIZE,SIZE);
  }
  else{
    printf("Tamanho da matriz: ");
    scanf("%d",&SIZE);
  }

  n_iter = SIZE/(n_threads+1);

  //inicia as matrizes
  for (k = 0; k < n_threads; k++){
    id_thread[k] = k;

    if(pthread_create(&tid[k],NULL,inicia_matrizes,(void *)&id_thread[k])){
      printf("Cannot create thread %d\n",i);
      exit(1);
    }
  }

  inicia_matrizes((void *)&p);

  /* join threads */
  for (i = 0; i < n_threads; i++){
        pthread_join(tid[i],NULL);
  }

  //multiplica as matrizes
  for (k = 0; k < n_threads; k++){
    id_thread[k] = k;

    if(pthread_create(&tid[k],NULL,multiplica_matrizes,(void *)&id_thread[k])){
      printf("Cannot create thread %d\n",i);
      exit(1);
    }
  }

  multiplica_matrizes((void *)&p);
  /* join threads */
  for (i = 0; i < n_threads; i++){
        pthread_join(tid[i],NULL);
  }

  printf("c[0][0]=%f   c[15][20]=%f  c[30][40]=%f  c[%d][%d]=%f \n",c[0][0],c[15][20],c[30][40],SIZE-1,SIZE-1,c[SIZE-1][SIZE-1]);
  printf("Fim!\n");
}