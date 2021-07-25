#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define n_processes 3
int SIZE;

typedef struct {
   double a[2000][2000], b[2000][2000], c[2000][2000];
} matrizes;

matrizes *matriz;
pid_t pid_p;

void main(argc, argv)
int argc;
char **argv;
{

  if (argc > 1){
    SIZE = atoi(argv[1]);
    printf("Matriz %dx%d\n",SIZE,SIZE);
  }
  else{
    printf("Tamanho da matriz: ");
    scanf("%d",&SIZE);
  }

  int i,j,k,id_proc;
  int status;
  struct shmid_ds *buf;
  int id_matriz;
  int n_iter,inicio,fim;
  pid_t pid[n_processes];

  id_matriz = shmget(IPC_PRIVATE, sizeof(matrizes), 0777 | IPC_CREAT);
  matriz = shmat(id_matriz, 0, 0);

  n_iter = SIZE/(n_processes + 1);
  inicio = 0;
  fim = n_iter;
  id_proc = -1;

  do {
    id_proc++;
    pid_p = fork();

    if ((int)pid_p != 0){
      pid[id_proc] = pid_p;
    }   //pai
  } while((pid_p != 0) & (id_proc < (n_processes-1)));

  if ((int)pid_p == 0){     //filhos
    matriz = shmat(id_matriz, 0, 0);
    inicio = (id_proc+1) * n_iter;
    fim = inicio + n_iter;
  }

  printf("inicio=%d  fim=%d   k=%d   n_iter=%d\n",inicio,fim,id_proc,n_iter);

  for(i = inicio; i < fim; i++){
    for(j = 0; j < SIZE; j++){
      ((matrizes *)matriz)->a[i][j] = i+j;
      ((matrizes *)matriz)->b[i][j] = i-j;
      ((matrizes *)matriz)->c[i][j] = (double)0.0;
    }

    if ((int)pid_p == 0){     // termina os processos filhos
      shmdt(matriz);
      exit(1);
    }
  }

  // fim da inicializacao
  for(id_proc = 0; id_proc < n_processes; id_proc++){
    waitpid(pid[id_proc],&status,0);
  }


  // multiplicação de matrizes

  if ((int)pid_p != 0){
    for(id_proc = 0; id_proc < n_processes; id_proc++){
      waitpid(pid[id_proc],&status,0);
    }

    n_iter = SIZE/(n_processes + 1);
    inicio = 0;
    fim = n_iter;
    id_proc = -1;

    do {
      id_proc++;
      pid_p = fork();

      if ((int)pid_p != 0)   // processo pai
        pid[id_proc] = pid_p;

     } while((pid_p != 0) & (id_proc < (n_processes-1)));

    if ((int)pid_p == 0){     // processos filhos
      matriz = shmat(id_matriz, 0, 0);
      inicio = (id_proc+1) * n_iter;
      fim = inicio + n_iter;
    }

    for(i = inicio; i < fim; i++){
      for(k = 0; k < SIZE; k++){
        for(j = 0; j < SIZE; j++){
          ((matrizes *)matriz)->c[i][j] += ((matrizes *)matriz)->a[i][k] * ((matrizes *)matriz)->b[k][j];
        }
      }
    }

    if ((int)pid_p == 0){     // termina os processos filhos
      shmdt(matriz);
      exit(1);
    }

    // fim da multiplicacao

    for(id_proc = 0; id_proc < n_processes; id_proc++){ // espera fim dos processos
      waitpid(pid[id_proc],&status,0);
    }


    printf("c[0][0]=%f   c[15][20]=%f  c[30][40]=%f  c[%d][%d]=%f \n",((matrizes *)matriz)->c[0][0],((matrizes *)matriz)->c[15][20],((matrizes *)matriz)->c[30][40],SIZE-1,SIZE-1,((matrizes *)matriz)->c[SIZE-1][SIZE-1]);

    shmdt(matriz);
    shmctl(id_matriz, IPC_RMID, buf); //remove area compartilhada
    printf("Fim!\n");
  }
}