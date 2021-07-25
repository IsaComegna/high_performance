#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h> 

#define size 1000
#define n_processos 3

typedef struct {
   double a[1000][1000], b[1000][1000];
} matrizes;

matrizes *matriz;
pid_t pid_p;

void main()
{  
  int i,j,id_proc;
  pid_t pid[n_processos];
  int status;
  struct shmid_ds *buf;
  int id_matriz;
  int n_iter,inicio,fim;

  id_matriz = shmget(IPC_PRIVATE, sizeof(matrizes), 0777 | IPC_CREAT);
  matriz = shmat(id_matriz, 0, 0);

  //inicializa as matrizes   -  3 processos
  n_iter = size/(n_processos + 1);
  inicio = 0;
  fim = n_iter;
  id_proc = -1;

  do {
    id_proc++; 
    pid_p = fork();

    if ((int)pid_p != 0)   //pai
      pid[id_proc] = pid_p;

   } while((pid_p != 0) & (id_proc < (n_processos-1)));

  if ((int)pid_p == 0){     //filhos
    matriz = shmat(id_matriz, 0, 0);
    inicio = (id_proc+1) * n_iter;
    fim = inicio + n_iter;
  }

  printf("inicio=%d  fim=%d   k=%d   n_iter=%d\n",inicio,fim,id_proc,n_iter);

  for(i = inicio; i < fim; i++)
    for(j = 0; j < size; j++){
      ((matrizes *)matriz)->a[i][j] = 1.5;
      ((matrizes *)matriz)->b[i][j] = 2.6;
    }

  if ((int)pid_p == 0){     //filhos
    shmdt(matriz);
    exit(1);
  }

  // fim da inicializacao
  for(id_proc = 0; id_proc < n_processos; id_proc++) 
    waitpid(pid[id_proc],&status,0);

  printf("a[0][0]=%f   a[15][20]=%f  b[15][20]=%f  b[%d][%d]=%f \n",((matrizes *)matriz)->a[0][0],((matrizes *)matriz)->a[15][20],((matrizes *)matriz)->b[15][20],size-1,size-1,((matrizes *)matriz)->b[size-1][size-1]);
  shmdt(matriz);
  shmctl(id_matriz, IPC_RMID, buf); //remove area compartilhada
}