/*
 * @author:  Allan Jair Escamilla Hernández
 * @date:    12/octubre/2019
 * @file:    dijkstra.c
 * @brief:  Implementacion del algortmo Dijkstra a un grafo.
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct defNodo{
    char etiqueta;
    int cantidadConexiones, coincidencias;
    int *costo;
    struct defNodo **conexiones;
} Nodo;

typedef struct defTabla{
    int *sdf;
    char *vertex;
    char *prevVertex;
    int counter;
    unsigned int visited;
}Tabla;

// Estructuras de las funciones
void Dijkstra(Nodo *Inicio, Tabla *tabla, int counter, char previoLabel, int cuentaNodos, int cant);
void inicializarTabla(Tabla *tabla, int cantidad);
int buscarPosicion(char *vertex, char etiqueta, int cuentaNodos);
void calcular_ruta(Tabla t1, int cantidad);



/* * Funcion que inicializa la tabla que contendra los caminos.
   * @param Tabla* tabla recibe la tabla donde se calcularan los caminos mas cortos.
   * @param int cantidad recibe la cantidad de nodos en el grafo.
*/
void inicializarTabla(Tabla* tabla, int cantidad){
    char init = 'a';
    tabla->sdf = (int*)malloc(sizeof(int) * cantidad);
    tabla->vertex = (char*)malloc(sizeof(char) * cantidad);
    tabla->prevVertex = (char*)malloc(sizeof(char) * cantidad);
    for(int i = 0; i < cantidad; i++){
        tabla->vertex[i] = init;
        tabla->sdf[i] = 100000;
        init++;
    }
}

/* * Funcion que implementa el algoritmo de Dijkstra.
   * @param Nodo* Inicio recibe el nodo inicial del grafo.
   * @param Tabla tabla recibe la tabla donde se calcularon los caminos mas cortos.
   * @param int counter recibe una variable que cuenta los costos de llegar a un nodo u otro.
   * @param char previoLabel recibe el label anterior al nodo actual en el grafo.
   * @param int cuentaNodos recibe la cantidad de nodos en el grafo.
   * @param int cant es la cantidad de conexiones que tiene cada nodo.
*/
void Dijkstra(Nodo *Inicio, Tabla *tabla, int counter, char previoLabel, int cuentaNodos, int cant){
    int contador = 0;
    unsigned int visited = 0, temp = 0, temp2;
    int bits = sizeof(unsigned int) * 8 - cuentaNodos;
    printf("%d\n", bits);
    while (contador < cant){
            int posicion = buscarPosicion(tabla->vertex, Inicio->etiqueta, cuentaNodos);
            temp2 = visited;
            temp = 1;
            temp <<= bits + posicion;
            visited |= temp;
            if(!(visited == temp2)){
                printf("Visitados: %u\n", visited);
                if (counter < tabla->sdf[posicion]){
                    tabla->sdf[posicion] = counter;
                    tabla->prevVertex[posicion] = previoLabel;
                }
                if (Inicio->conexiones[contador] != NULL){
                    Dijkstra(Inicio->conexiones[contador], tabla, counter + Inicio->costo[contador], Inicio->etiqueta, cuentaNodos, cant);
                    visited = temp2;
                }
            }
        contador++;
    }
}

/* * Funcion que busca la posicion de un nodo dentro de la tabla.
   * @param char vertex recibe un arreglo de vertices donde se va a buscar un nodo.
   * @param char etiqueta recibe el valor que se va a buscar.
   * @param int cuentaNodos recibe la cantidad de nodos que hay en el grafo.
*/
int buscarPosicion(char *vertex, char etiqueta, int cuentaNodos){
    for(int i = 0; i < cuentaNodos; i++)
        if(vertex[i] == etiqueta)
            return i;
}

/* * Funcion que calcula la ruta mas corta basandose en la tabla que se ha calculado anteriormente.
   * @param int cantidad recibe la cantidad de conexiones que tiene cada nodo dentro del grafo.
*/
void calcular_ruta(Tabla t1, int cantidad){
    char nodo, etiqueta;
    int p = 0, min = 0;
    printf("Ingresar al nodo de la red al que desea llegar-> ");
    __fpurge(stdin);
    scanf("%c", &nodo);
    for(int i = 0; i < cantidad; i++)
        if(t1.vertex[i] == nodo){
            p = 1;
            min = t1.sdf[i];
        }
    if(p == 0){
        printf("El nodo no se encuentra en la red):\n");
        return;
    }
    printf("La ruta mas corta es: ");
    etiqueta = nodo;
    printf("%c <- ", etiqueta);
    while (etiqueta != 'a'){
        for(int i = 0; i < cantidad; i++)
            if(t1.vertex[i] == etiqueta){
                etiqueta = t1.prevVertex[i];
                break;
            }
        printf("%c <- ", etiqueta);
    }
    printf("\nEl costo total de este camino es de %d\n", min);
}