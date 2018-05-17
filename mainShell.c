#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "shellnb.c"

int main(int argc, char const *argv[]){
  char * comando = malloc(200);
 
  while(1){
    printf("-> ");
    scanf("%[^\n]%*c",comando);

    if (!strcmp("exit", comando)){
      printf("\n>> Liberando memoria\n");
      free(comando);
      break;
    }
    else{
      sinEspacios(comando);
      if(hijo() == 0){
        break;
      }
    }
  }
}