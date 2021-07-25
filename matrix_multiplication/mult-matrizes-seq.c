/*multiplicacao de matrizes*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "mede_time.h"

int SIZE;

double a[2000][2000];
double b[2000][2000];
double c[2000][2000]; 

/*inicia matrizes*/
void inicia_matrizes()
{ 
  int i, j;

  for(i = 0; i < SIZE; i++){  
    for (j = 0; j < SIZE; j++){
      a[i][j] = i + j;
      b[i][j] = i - j;
      c[i][j] = (double)0.0;
    }
  }
}


/*multiplicacao*/
void mat_mult()
{
  int i, j, k;

  for(i = 0; i < SIZE; i++){
    for(k = 0; k < SIZE; k++) 
      for(j = 0; j < SIZE; j++)
        c[i][j] = c[i][j] + a[i][k] * b[k][j];
  }
}

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
 
  TIMER_CLEAR;
  TIMER_START; 
  inicia_matrizes();
  TIMER_STOP;
  printf ("TEMPO INICIA [SIZE %d]: %12.7f\n",SIZE,TIMER_ELAPSED);
  TIMER_CLEAR;
  TIMER_START; 
  mat_mult();
  TIMER_STOP;
  printf ("TEMPO MULTIPLICA [SIZE %d]: %12.7f\n",SIZE,TIMER_ELAPSED);
  printf ("c[0][0]=%f  c[2][1]=%f c[%d][%d]=%f\n",c[0][0],c[2][1],SIZE-1,SIZE-1,c[SIZE-1][SIZE-1]);
}