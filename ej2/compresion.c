#include <stdio.h> // Incluyendo las librerias
#include <stdlib.h>

// Prototipos de las funciones
unsigned short int comprimirNumeros(int cantArg, char* Argumentos[]);

// Funcion principal
int main(int argc, char *argv[]) {
  //printf("%ld\n", sizeof(unsigned short int));
  unsigned short int number = 0;
  number = comprimirNumeros(argc, argv);
  printf("El numero comprimido es: %d\n", number);
  return 0;
}

// DESARROLLANDO LAS FUNCIONES

// Funcion que comprime los 4 numeros en un solo integer
unsigned short int comprimirNumeros(int cantArg, char* Argumentos[]){
  unsigned short int number = 0;
  int cant = 3, aux;
  if(cantArg > 5 )
    return 0;
  for(int i = 1; i < cantArg; i++){ // Recorriendo el array
    aux = atoi(Argumentos[i]);
    if (atoi(Argumentos[i]) && aux >= 0 && aux <= 16) { // Validando los numeros que se han ingresado
      number+= (aux << (cant*4));
      cant--;
    }else{
      printf("Ha ocurrido un error con los argumentos...\nSaliendo del programa...\n");
      exit(0);
      return 0;
    }
  }
  return number; // Retornando el numero comprimido
}
