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
void anadirNodo(LD** Init, int conexiones, char* etiqueta);
Nodo** generarArray(int conexiones);
void agregaraListaD(LD** Init, Nodo* tempo);
void anadirArista(LD* Init, int con);
void limpiarMemoria(LD* Init);
void desplegarGrafo();

int main(){
  Nodo* Inicio = NULL;
  LD* Init = NULL, *temp;
  int conexiones;
  int opc = 0;
  char etiqueta = 'a';
  printf("Ingresar la cantidad de conexiones-> ");
  scanf("%d", &conexiones);
  do {
    system("clear");
    printf("1.- Aniadir nodo.\n");
    printf("2.- Aniadir arista.\n");
    printf("Ingresar opcion-> ");
    scanf("%d", &opc);
    switch (opc) {
      case 1:
        anadirNodo(&Init, conexiones, &etiqueta);
        break;
      case 2:
        anadirArista(Init, conexiones);
        break;
    }
    printf("Presiona enter para continuar... ");
    __fpurge(stdin);
    getchar();
  } while(opc != 0);
  temp = Init;
  while (temp != NULL) {
    printf("%c ", temp->nd->etiqueta);
    temp = temp->sig;
  }
  printf("\n");
  limpiarMemoria(Init);
  return 0;
}

void anadirNodo(LD** Init, int conexiones, char* etiqueta){
  Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
  temp->etiqueta = *etiqueta;
  temp->cantidadConexiones = 0;
  temp->conexiones = generarArray(conexiones);
  for(int i = 0; i < conexiones; i++){
    temp->conexiones[i] = NULL;
  }
  *etiqueta = *etiqueta + 1;
  agregaraListaD(Init, temp);
}

Nodo** generarArray(int conexiones){
  return (Nodo**)malloc(conexiones*sizeof(Nodo*));
}

void agregaraListaD(LD** Init, Nodo* tempo){
  LD* temp = (LD*)malloc(sizeof(LD)), *temp2;
  temp->nd = tempo;
  temp->sig = NULL;
  if(*Init == NULL)
    (*Init) = temp;
  else{
    temp2 = *Init;
    while (temp2->sig != NULL) {
      temp2 = temp2->sig;
    }
    temp2->sig = temp;
  }
}

void anadirArista(LD* Init, int con){
  LD* temp1 = Init, *temp2 = Init;
  char c1, c2;
  __fpurge(stdin);
  printf("Ingresar nodo al que se quiere agregar la conexion-> ");
  scanf("%c", &c1);
  while (temp1 != NULL && temp1->nd->etiqueta != c1) {
    temp1 = temp1->sig;
  }
  __fpurge(stdin);
  printf("Ingresar nodo al que se quiere conectar-> ");
  scanf("%c", &c2);
  while (temp2 != NULL && temp2->nd->etiqueta != c2) {
    temp2 = temp2->sig;
  }
  if(temp1 == NULL || temp2 == NULL){
    printf("No existe alguno de los caracteres ingresados\n");
    return;
  }
  if(temp1->nd->cantidadConexiones < con && temp2->nd->cantidadConexiones < con){
    temp1->nd->conexiones[temp1->nd->cantidadConexiones] = temp2->nd;
    temp1->nd->cantidadConexiones = temp1->nd->cantidadConexiones + 1;
    temp2->nd->conexiones[temp2 ->nd->cantidadConexiones] = temp1->nd;
    temp2->nd->cantidadConexiones = temp2->nd->cantidadConexiones + 1;
  }else{
    printf("Alguno de los nodos seleccionados ya no tiene espacio para mas conexiones):\n");
  }

}

void limpiarMemoria(LD* Init){
  LD* temp = Init, *temp2;
  while(temp != NULL){
    free(temp->nd);
    temp2 = temp;
    temp = temp->sig;
    free(temp2);
  }
}
