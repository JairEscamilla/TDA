#include <stdio.h>
#include <stdlib.h>

unsigned short int comprimirNumeros(int cantArg, char* Argumentos[]);

int main(int argc, char *argv[]) {
  //printf("%ld\n", sizeof(unsigned short int));
  unsigned short int number = 0;
  number = comprimirNumeros(argc, argv);
  printf("El numero comprimido es: %d\n", number);
  return 0;
}

unsigned short int comprimirNumeros(int cantArg, char* Argumentos[]){
  unsigned short int number = 0;
  int cant = 3, aux;
  for(int i = 1; i < cantArg; i++){
    aux = atoi(Argumentos[i]);
    number+= (aux << (cant*4));
    cant--;
  }
  return number;
}
