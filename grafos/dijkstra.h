/*
 * @author:  Allan Jair Escamilla Hernández
 * @date:    12/octubre/2019
 * @file:    dijkstra.c
 * @brief:  Implementacion del algortmo Dijkstra a un grafo.
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct defTabla{
    int *sdf;
    char *vertex;
    char *prevVertex;
    int counter;
    unsigned int visited;
}Tabla;

// Estructuras de las funciones
void startVisited(Tabla *tabla, int cantiad);

// Desarrollando las funciones
void startVisited(Tabla *tabla, int cantidad){
    tabla->visited = 0;
    for(int i = 0; i < cantidad; i++){
        (tabla->visited) += (1 << i);
    }
}