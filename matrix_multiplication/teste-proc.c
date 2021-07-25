// PROCESSOS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
   pid_t pid[3];
   int status;
   char x;
   int i;

   pid[0] = fork();
   if ((int)pid[0] == 0){
      x = 'a';
      for(i = 0; i < 100000; i++){
         printf("%c",x);
         fflush(stdout);
      }
      exit(1);
   }

   pid[1] = fork();
   if ((int)pid[1] == 0) {
      x = 'b';
      for(i = 0; i < 100000; i++){
         printf("%c",x);
         fflush(stdout);
      }
      exit(1); 
   }

   pid[2] = fork();
   if ((int)pid[2] == 0) {
      x = 'c';
      for(i = 0; i < 100000; i++){
         printf("%c",x);
         fflush(stdout);
      }
      exit(1);
   }

 /*
   for (i=0;i<3;i++)
      waitpid(pid[i],&status,0);
*/
   printf("\nFIM\n");
 }