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
void startVisited(Tabla *tabla, int cantiad);
void Dijkstra(Nodo *Inicio, Tabla *tabla, int conexiones, int iteracion, unsigned int visitados, int counter, char previoLabel);
int minimoCamino(int* Array, int conexiones);
void inicializarTabla(Tabla *tabla, int cantidad);

// Desarrollando las funciones

// FUNCION QUE INICIALIZA LOS NODOS VISITADOS
void startVisited(Tabla *tabla, int cantidad){
    tabla->visited = 0;
    for(int i = 0; i < cantidad; i++){
        (tabla->visited) += (1 << i);
    }
}

void inicializarTabla(Tabla* tabla, int cantidad){
    char init = 'a';
    tabla->sdf = (int*)malloc(sizeof(int) * cantidad);
    tabla->vertex = (char*)malloc(sizeof(char) * cantidad);
    tabla->prevVertex = (char*)malloc(sizeof(char) * cantidad);
    for(int i = 0; i < cantidad; i++){
        tabla->vertex[i] = init;
        init++;
    }
}

void Dijkstra(Nodo *Inicio, Tabla *tabla, int conexiones, int iteracion, unsigned int visitados, int counter, char previoLabel){
    visitados += 1 << (31 - iteracion);
    printf("Visitados: %d\n", visitados);
    int minimimo = minimoCamino(Inicio->costo, conexiones);
    
    // printf("EL camino minimo es %c\n", Inicio->conexiones[minimimo]->etiqueta);
}

int minimoCamino(int* Array, int conexiones){
    int minimo = Array[0];
    for(int i = 0; i < conexiones; i++)
        if(Array[i] < minimo)
            minimo = Array[i];
    return minimo;
}