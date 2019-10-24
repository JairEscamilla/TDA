/*
 * @author:  Allan Jair Escamilla Hernández
 * @date:    18/octubre/2019
 * @file:    neuronas.c
 * @brief: Neuronas con valores predeterminados que resuelve el problema de las compuertas and, or y not.
 */

// INCLUYENDO BIBLIOTECAS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// DEFINIENDO LA ESTRUCTURA QUE TENDRA UNA NEURONA
typedef struct Neuronas{
    double* w;
    double bias;
    double* error;
}Neurona;

// PROTOTIPOS DE LAS FUNCIONES
double sumatoria(int x[], Neurona n);
int activacion(double sum);
void iniciarNeuronas(Neurona* and, Neurona* or, Neurona* not);
double randfrom(double min, double max);
void entrenarNeurona(Neurona* neuron, int inputs[4][2], int outputs[]);

// FUNCION PRINCIPAL
int main(){
    Neurona and, or, not; // Declarando las neuronas
    int op;
    int inputsAnd[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}}; 
    int outputsAnd[4] = {0, 0, 0, 1};
    int *x = (int*)malloc(sizeof(int)*2);
    // ASIGNANDO MEMORIA A LOS ARREGLOS QUE CONTENDRAN LOS PESOS DE LAS ENTRADAS
    and.w = (double*)malloc(sizeof(double)*2);
    and.error = (double*)malloc(sizeof(double)*2);
    or.w = (double*)malloc(sizeof(double)*2);
    not.w = (double*)malloc(sizeof(double)*2);
    iniciarNeuronas(&and, &or, &not); // Inicializando los valores de las neuronas
    entrenarNeurona(&and, inputsAnd, outputsAnd);
    do{
        system("clear");
        printf("1.-and\n2.-or\n3.-not\n4.-salir\nElegir una opcion: ");
        scanf("%d", &op);
        switch (op){
        case 1:
            for(int i = 0; i < 2; i++){
                printf("Ingresar entrada numero %d-> ", i);
                scanf("%d", &(x[i]));
            }
            printf("El resultado es %d\n", activacion(sumatoria(x, and)));
            break;
        case 2:
            for(int i = 0; i < 2; i++){
                printf("Ingresar entrada numero %d-> ", i);
                scanf("%d", &(x[i]));
            }
            printf("El resultado es %d\n", activacion(sumatoria(x, or)));
            break;
        case 3:
            printf("Ingresar entrada: ");
            scanf("%d", &(x[0]));
            x[1] = 0;
            printf("El resultado es %d\n", activacion(sumatoria(x, not)));
            break;
        case 4: 
            printf("Saliendo\n");
            break;
        default:
            printf("Ingresa una opcion valida!\n");
            break;
        }
        printf("Presionar enter para continuar...\n");
        __fpurge(stdin);
        getchar();
    } while (op != 4);
    // LIBERANDO MEMORIA ASIGNADA EN TIEMPO DE EJECUCION
    free(x);
    free(and.w);
    free(or.w);
    free(not.w);
}   

// DESARROLLANDO LAS FUNCIONES
        
/* * Funcion que hace la sumatoria de los pesos y las entradas de la neurona
   * @param int x[] recibe un arreglo de las entradas dadas por el usuario.
   * @param Neurona n recibe la neurona que contiene los pesos y el valor del sesgo para realizar la sumatoria.
*/
double sumatoria(int x[], Neurona n){
    double sum = 0;
    for(int i = 0; i < 2; i++)
        sum+= x[i]*n.w[i];
    return sum + n.bias; 
}

/* * Funcion que inicializa los pesos y sesgos de las neuronas.
   * @param Neurona* and recibe una neurona para asignar pesos.
   * @param Neurona* or recibe una neurona para asignar pesos.
   * @param Neurona* not recibe una neurona para asignar pesos.
*/
void iniciarNeuronas(Neurona* and, Neurona* or, Neurona* not){
    and->w[0] = randfrom(0, 1);
    and->w[1] = randfrom(0, 1);
    and->bias = randfrom(0, 1); 
    or->w[0] = 1;
    or->w[1] = 1;
    or->bias = 0;
    not->w[0] = -1;
    not->w[1] = 0;
    not->bias = 0.75;
}

/* * Funcion de activacion de las neuronas.
   * @param double sum recibe el resultado de la sumatoria para determinar la activacion o no de la neurona.
*/
int activacion(double sum){
    return sum >= 0.5;
}
double randfrom(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void entrenarNeurona(Neurona* neuron, int inputs[4][2], int outputs[]){
    FILE* Arch = fopen("neuronas.dat", "wt");
    int epochs = 10000;
    int counter = 0;
    double salida;
    double sum = 0, lr = 0.0001;
    for(int i = 0; i < epochs; i++){
        counter = 0;
        while (counter < 4){
            sum = 0;
            sum = sumatoria(inputs[counter], *neuron);
            //salida = sum >= 0;
            for(int j = 0; j < 2; j++)
                neuron->w[counter] = neuron->w[counter] + lr*(sum - outputs[counter])*inputs[counter][j];

            neuron->bias = neuron->bias + lr*(sum - outputs[counter]);
            counter++;
        }
        fprintf(Arch, "%f, %f, %f, %f\n", neuron->w[0], neuron->w[1], neuron->bias, sum - outputs[counter]);
    }
    fclose(Arch);
}

