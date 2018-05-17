#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

char * aux[100];

int hijo(){
  pid_t pid = fork();
  if(pid < 0){
    fprintf(stderr, "Error con el proceso hijo.\n");
    exit(1);
  }
  else if(pid == 0){
    if(execvp(aux[0],aux) == -1){
      printf("%s\n", "Error no se pudo ejecutar el comando ingresado.");
      return 0;
    }
  }else{
    wait(NULL);
  }

  return 1;
}

void sinEspacios(char* comando){
  const char attribute[2] = " ";
  char *head;
  int c=0;
 
  head = strtok(comando, attribute);
  aux[c]=head;

 
  while(head != NULL ) {
    c++;
 
    head = strtok(NULL, attribute);
    aux[c]=head;
  }
}
