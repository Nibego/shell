#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

char * auxCommand[100];

int pHijo(){
  pid_t pid = fork();
  if(pid < 0){
    fprintf(stderr, "Error con el proceso hijo.\n");
    exit(1);
  }
  else if(pid == 0){
    if(execvp(auxCommand[0],auxCommand) == -1){
      printf("%s\n", "Error no se pudo ejecutar el comando ingresado.");
      return 0;
    }
  }else{
    wait(NULL);
  }

  return 1;
}

void sinEspacios(char* comando){
  char valor[2] = " ";
  char * aux;
  int i = 0;
 
  aux = strtok(comando, valor);
  auxCommand[i] = aux;
 
  while(aux != NULL){
    aux = strtok(NULL, valor);
    auxCommand[++i] = aux;
  }
}

int redireccion(){
  char * aux;
  int i = 0;
  aux = auxCommand[i];

  while(aux!=NULL){
    if(strcmp(aux,">") == 0){
      return 1; //se encontro la cadena >
    }
    aux = auxCommand[++i];
  }
  return 0; //no se encontro la cadena >
}

//Guardar en archivo
int saveFile(){
  char * aux; //lugo del >
  char * aux2[200]; //Antes del >
  int i = 0;
  char rutaEnCarpetaActual[3] = "./";

  aux = auxCommand[i];
  //Buscamos hasta encontrar la posicion del > para el nombre del archivo.
  while( !(strcmp(">",aux) == 0) ){ 
    aux2[i] = aux;
    i++;
    aux = auxCommand[i];
  }

  pid_t pid = fork();
  if(pid < 0){
    fprintf(stderr, "Error con el proceso hijo.\n");
    exit(1);
  }
  else if(pid == 0){
    close(STDOUT_FILENO);
    //aux[i + 1] es el nombre del archivo
    int file = open(strcat(rutaEnCarpetaActual, auxCommand[i + 1]), O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);/*0S_IRUSR*/
    if(execvp(aux2[0],aux2) == -1){
      printf("No se pudo ejecutar el comando para guardar en el archivo.\n");
      return 0;
    }
    close(file);
  }else{
    wait(NULL);
  }
  return 1;
}