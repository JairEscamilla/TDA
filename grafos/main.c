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
void insertarNodo(Nodo** Raiz, char etiqueta, int conexiones);
void buscarNodo(Nodo *Raiz, int cant, int total, char buscado, Nodo **aux);
void agregarArista(Nodo *Raiz, int total);
    // Funcion principal
    int main()
{
    Nodo* Raiz = NULL, *Inicial;
    int opcion = 2, conexiones, i = 0;
    char etiqueta = 'a';
    do{
        printf("Ingresar la cantidad de conexiones por nodo-> ");
        scanf("%d", &conexiones);
        if (conexiones < 1)
            printf("Los nodos deben tener al menos una conexion\n");
    } while (conexiones < 1);
    do{
        system("clear");
        printf("1.- Insertar nodo.\n");
        printf("2.- Agregar arista.\n");
        printf("3.- Salir.\n");
        printf("\n\nSeleccione una opcion-> ");
        scanf("%d", &opcion);
        switch (opcion){
        case 1:
            insertarNodo(&Raiz, etiqueta, conexiones);
            etiqueta++;
            if(i == 0)
                Inicial = Raiz;
            i++;
            break;
        case 2:
            agregarArista(Raiz, conexiones);
            break;
        default:
            printf("Ingresa una opcion valida!\n");
            break;
        }
        printf("\nPresione enter para continuar... ");
        __fpurge(stdin);
        getchar();
    } while (opcion != 3);
    
    return 0;
}

// Desarrollando las funciones

void insertarNodo(Nodo **Raiz, char etiqueta, int conexiones){ // Funcion que inserta un nodo al grafo
    char NodoConnect;
    Nodo* aux = NULL;
    Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
    temp->etiqueta = etiqueta;
    temp->cantidadConexiones = 0;
    temp->conexiones = (Nodo**)malloc(sizeof(Nodo*) * conexiones);
    for(int i = 0; i < conexiones; i++)
        temp->conexiones[i] = NULL; 
    if(*Raiz == NULL)
        *Raiz = temp;
    else{
        do{
            printf("Ingresar nodo al que desea conectar el nodo creado: ");
            __fpurge(stdin);
            scanf("%c", &NodoConnect);
            buscarNodo(*Raiz, 0, conexiones, NodoConnect, &aux);
            if (aux == NULL)
                printf("El nodo ingresado no existe en el grafo, asegurese de ingresar uno que realmente exista!\n\n");
        } while (aux == NULL);
        temp->conexiones[temp->cantidadConexiones] = aux;
        temp->cantidadConexiones = temp->cantidadConexiones + 1;
        *Raiz = temp;
        printf("Se ha insertado correctamente el nodo al grafo!\n\n");
    }
}

void buscarNodo(Nodo* Raiz, int cant, int total, char buscado, Nodo** aux){
    if (Raiz->etiqueta != buscado){
        while (cant < total){
            if (Raiz->conexiones[cant] != NULL)
                buscarNodo(Raiz->conexiones[cant], cant, total, buscado, aux);
            cant++;
        }
    }else{
        printf("Nodo encontrado\n");
        *aux = Raiz;
    }
}

void agregarArista(Nodo* Raiz, int total){
    char etiqueta1, etiqueta2;
    Nodo* agregarArista = NULL, *recibirConexion = NULL;
    printf("Ingresar el nodo al que desea agregar la arista-> ");
    __fpurge(stdin);
    scanf("%c", &etiqueta1);
    buscarNodo(Raiz, 0, total, etiqueta1, &agregarArista);  
    printf("Ingresar el nodo al que se va a conectar el nodo anterior-> ");
    __fpurge(stdin);
    scanf("%c", &etiqueta2);
    buscarNodo(Raiz, 0, total, etiqueta2, &recibirConexion);  
    if(agregarArista == NULL || recibirConexion == NULL){
        printf("Alguno de los nodos ingresados no existe\n");
        return;
    }
    if(agregarArista->cantidadConexiones >= total){
        printf("Este nodo ya no tiene espacio para mas conexiones\n");
        return;
    }
    agregarArista->conexiones[agregarArista->cantidadConexiones] = recibirConexion;
    agregarArista->cantidadConexiones = agregarArista->cantidadConexiones + 1;

}
