/*
 * @author:  Allan Jair Escamilla Hernández
 * @date:    17/septiembre/2019
 * @file:    grafos.c
 * @brief:  Implementacion de un generador de grafos.
 * -> Con una estructura de datos en C generar un tipo de datos "nodo" que contenga n conexiones definidas por el usuario.
 * -> Implementar las funciones de : anadir_nodo, anadir_vertice, desplegar_grafo, buscar_dato.
 * -> Cada nodo será etiquetado por su orden de insercion.
 */
#include"dijkstra.h" // Incluyo las bibliotecas

// ESTRUCTURA DEL GRAFO

// Prototipos de las funciones
void insertarNodo(Nodo** Raiz, char etiqueta, int conexiones);
void buscarNodo(Nodo *Raiz, int cant, int total, char buscado, Nodo **aux);
void agregarArista(Nodo *Raiz, int total);
void buscarDato(Nodo *Raiz, int total);
void desplegar_grafo(Nodo* Raiz, int cant, int total);
void liberar_memoria(Nodo** Raiz, int cant, int total);
void contarCoincidencias(Nodo **Raiz, int cant, int total);

// Funcion principal
int main(){
    Nodo* Raiz = NULL, *Inicial;
    int opcion = 2, conexiones, i = 0, cuentaNodos = 0;
    char etiqueta = 'a';
    unsigned int visitados = 0;
    int cuentaPasos = 0;
    Tabla t1;
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
        printf("3.- Buscar dato.\n");
        printf("4.- Desplegar grafo.\n");
        printf("5.- Calcular tabla\n");
        printf("6.- Salir.\n");
        printf("\n\nSeleccione una opcion-> ");
        scanf("%d", &opcion);
        switch (opcion){
        case 1:
            insertarNodo(&Raiz, etiqueta, conexiones);
            etiqueta++;
            if(i == 0)
                Inicial = Raiz;
            i++;
            cuentaNodos++;
            break;
        case 2:
            agregarArista(Raiz, conexiones);
            break;
        case 3:
            buscarDato(Raiz, conexiones);
            break;
        case 4:
            desplegar_grafo(Raiz, 0, conexiones);
            break;
        case 5:
            inicializarTabla(&t1, cuentaNodos);
            Dijkstra(Raiz, &t1, conexiones, 0, visitados, cuentaPasos, Raiz->etiqueta);
            break;
        case 6:
            if(Raiz != NULL){
                contarCoincidencias(&Raiz, 0, conexiones);
                liberar_memoria(&Raiz, 0, conexiones);
            }
            printf("Saliendo del programa... \n");
            exit(0);
            break;
        default:
            printf("Ingresa una opcion valida!\n");
            break;
        }
        printf("\nPresione enter para continuar... ");
        __fpurge(stdin);
        getchar();
    } while (opcion != 6);
    
    return 0;
}

// Desarrollando las funciones

void insertarNodo(Nodo **Raiz, char etiqueta, int conexiones){ // Funcion que inserta un nodo al grafo
    char NodoConnect;
    Nodo* aux = NULL;
    Nodo* temp = (Nodo*)malloc(sizeof(Nodo));
    temp->etiqueta = etiqueta;
    temp->cantidadConexiones = 0;
    temp->coincidencias = 0;
    temp->conexiones = (Nodo**)malloc(sizeof(Nodo*) * conexiones);
    temp->costo = (int*)malloc(sizeof(int)*conexiones);
    for(int i = 0; i < conexiones; i++)
        temp->conexiones[i] = NULL; 
    if(*Raiz == NULL)
        *Raiz = temp;
    else{
        do{
            printf("Ingresar el nodo al que va conectado: ");
            scanf(" %c", &NodoConnect);
            buscarNodo(*Raiz, 0, conexiones, NodoConnect, &aux);
            if (aux == NULL)
                printf("El nodo ingresado no existe en el grafo, asegurese de ingresar uno que realmente exista!\n\n");
        } while (aux == NULL);
        if(aux->cantidadConexiones < conexiones){
            printf("Ingresar el costo: ");
            scanf("%d", &(aux->costo[aux->cantidadConexiones]));
            aux->conexiones[aux->cantidadConexiones] = temp;
            (aux->cantidadConexiones)++;
            printf("%d\n", aux->cantidadConexiones);
            printf("Se ha insertado correctamente el nodo al grafo!\n\n");
        }else{
            printf("Ya no hay espacio para mas conexiones\n");
        }
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

void desplegar_grafo(Nodo* Raiz, int cant, int total){
    while (cant < total){
            if (Raiz->conexiones[cant] != NULL){

                desplegar_grafo(Raiz->conexiones[cant], cant, total);
                
            }
            if(cant == total - 1){
                printf("%c, ", Raiz->etiqueta);
            }
            cant++;
    }
}

void buscarDato(Nodo* Raiz, int total){
    char etiqueta;
    Nodo* aux = NULL;
    printf("Ingresar nodo a buscar-> ");
    __fpurge(stdin);
    scanf("%c", &etiqueta);
    buscarNodo(Raiz, 0, total, etiqueta, &aux);
    if(aux == NULL){
        printf("No se ha encontrado el dato\n");
        return;
    }
    printf("%c-> ", aux->etiqueta);
    for(int i = 0; i < total; i++)
        if(aux->conexiones[i] != NULL)
            printf("%c-> ", aux->conexiones[i]->etiqueta);
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
    printf("Se ha agregado la arista con exito\n");
}

void liberar_memoria(Nodo** Raiz, int cant, int total){
    while (cant < total){
            if ((*Raiz)->conexiones[cant] != NULL){

                liberar_memoria(&((*Raiz)->conexiones[cant]), cant, total);
                
            }
            if(cant == total - 1)
                (*Raiz)->coincidencias = (*Raiz)->coincidencias - 1;
            if((*Raiz)->coincidencias == 0)
                free(*Raiz);
            
            cant++;
    }
}

void contarCoincidencias(Nodo **Raiz, int cant, int total){
    while (cant < total){
        if ((*Raiz)->conexiones[cant] != NULL){

            liberar_memoria(&((*Raiz)->conexiones[cant]), cant, total);
        }
        if (cant == total - 1){
            (*Raiz)->coincidencias = (*Raiz)->coincidencias + 1;
        }
        cant++;
    }
}