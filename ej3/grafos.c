/*
 * @author:  Allan Jair Escamilla Hernández
 * @date:    17/septiembre/2019
 * @file:    grafos.c
 * @brief:  Implementacion de un generador de grafos.
 * -> Con una estructura de datos en C generar un tipo de datos "nodo" que contenga n conexiones definidas por el usuario.
 * -> Implementar las funciones de : anadir_nodo, anadir_vertice, desplegar_grafo, buscar_dato.
 * -> Cada nodo será etiquetado por su orden de insercion.
 */

#include <stdio.h> // Incluyendo las librerias
#include <stdlib.h>

// Definiendo la estructura del nodo
typedef struct defNodo{
  char etiqueta;
  int cantidadConexiones;
  struct defNodo** conexiones;
}Nodo;

typedef struct defLD{
  Nodo* nd;
  struct defLD* sig;
}LD;

// Prototipos de funciones
void anadirNodo(Nodo** Inicio, int conexiones, char* etiqueta);
Nodo** generarArray(int conexiones);

int main(){
  Nodo* Inicio = NULL;
  LD* Init = NULL;
  int conexiones;
  int opc = 0;
  char etiqueta = 'a';
  printf("Ingresar la cantidad de conexiones-> ");
  scanf("%d", &conexiones);
  do {
    printf("1.- Aniadir nodo.\n");
    printf("Ingresar opcion-> ");
    scanf("%d", &opc);
    anadirNodo(&Inicio, conexiones, &etiqueta);
  } while(opc != 0);
  return 0;
}

void anadirNodo(Nodo** Inicio, int conexiones, char* etiqueta){
  Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
  temp->etiqueta = *etiqueta;
  temp->conexiones = generarArray(3);
  for(int i = 0; i < conexiones; i++){
    temp->conexiones[i] = NULL;
  }
}

Nodo** generarArray(int conexiones){
  return (Nodo**)malloc(conexiones*sizeof(Nodo*));
}
