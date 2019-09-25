/*
 * @author:  Allan Jair Escamilla Hernández
 * @date:    17/septiembre/2019
 * @file:    grafos.c
 * @brief:  Implementacion de un generador de grafos.
 * -> Con una estructura de datos en C generar un tipo de datos "nodo" que contenga n conexiones definidas por el usuario.
 * -> Implementar las funciones de : anadir_nodo, anadir_vertice, desplegar_grafo, buscar_dato.
 * -> Cada nodo será etiquetado por su orden de insercion.
 */
#include<stdio.h> // Incluyo las bibliotecas
#include<stdlib.h>

// ESTRUCTURA DEL GRAFO
typedef struct defNodo{
    char etiqueta;
    int cantidadConexiones;
    struct defNodo **conexiones;
}Nodo;

// Prototipos de las funciones


// Funcion principal
int main(){
    Nodo* Raiz = NULL;
    int opcion = 2;
    do
    {
        system("clear");
        printf("1.- Insertar nodo.\n");
        printf("2.- Salir.\n");
        printf("\n\nSeleccione una opcion-> ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("Ingresando\n");
            break;
        
        default:
            printf("Ingresa una opcion valida!\n");
            break;
        }
        printf("\nPresione enter para continuar... ");
        __fpurge(stdin);
        getchar();
    } while (opcion != 2);
    
    return 0;
}

// Desarrollando las funciones