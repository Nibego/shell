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

    if (!strcmp("exit", comando)){ //Salida del padre
      printf("\n>> Saliendo y Liberando memoria\n");
      free(comando);
      break;
    }
    else{
      sinEspacios(comando); //Quitamos los espacios
      if(redireccion()){ //Comprobamos si existe redireccion a un archivo
        if(saveFile() == 0){
          break;
        }
      }
      else{
        if(pHijo() == 0){//Ejecutamos y comprobamos si el comando existe para cerrar el hilo.
          break;
        }
      }
    }
  }
}