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
void Dijkstra(Nodo *Inicio, Tabla *tabla, int conexiones, int iteracion, unsigned int visitados, int counter, char previoLabel, int cuentaNodos, int cant);
int minimoCamino(int* Array, int conexiones);
void inicializarTabla(Tabla *tabla, int cantidad);
int buscarPosicion(char *vertex, char etiqueta, int cuentaNodos);
void calcular_ruta(Tabla t1, int cantidad);

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
        tabla->sdf[i] = 100000;
        init++;
    }
}

void Dijkstra(Nodo *Inicio, Tabla *tabla, int conexiones, int iteracion, unsigned int visitados, int counter, char previoLabel, int cuentaNodos, int cant){
    int contador = 0;
    while (contador < cant){
        int posicion = buscarPosicion(tabla->vertex, Inicio->etiqueta, cuentaNodos);
        if (counter < tabla->sdf[posicion]){
            tabla->sdf[posicion] = counter;
            tabla->prevVertex[posicion] = previoLabel;
        }
        if (Inicio->conexiones[contador] != NULL){
            Dijkstra(Inicio->conexiones[contador], tabla, conexiones, iteracion, visitados, counter + Inicio->costo[contador], Inicio->etiqueta, cuentaNodos, cant);
        }
        contador++;
    }
}

int minimoCamino(int* Array, int conexiones){
    int minimo = Array[0];
    for(int i = 0; i < conexiones; i++)
        if(Array[i] < minimo)
            minimo = Array[i];
    return minimo;
}

int buscarPosicion(char *vertex, char etiqueta, int cuentaNodos){
    for(int i = 0; i < cuentaNodos; i++)
        if(vertex[i] == etiqueta)
            return i;
}

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