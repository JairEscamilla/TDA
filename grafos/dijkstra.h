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
}Tabla;

