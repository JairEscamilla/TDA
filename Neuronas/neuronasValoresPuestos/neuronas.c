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
#include<string.h>
// DEFINIENDO LA ESTRUCTURA QUE TENDRA UNA NEURONA
typedef struct Neuronas{
    double* w;
    double bias;
}Neurona;

// PROTOTIPOS DE LAS FUNCIONES
double sumatoria(double x[], Neurona n);
int activacion(double sum);
void iniciarNeuronas(Neurona* and, Neurona* or, Neurona* not);
double randfrom(double min, double max);
void entrenarNeurona(Neurona* neuron, double** training_data);
void entrenarNeuronaNot(Neurona *neuron, double** training_data);
double** get_training_data(char* gate, int numberOfPoints);
double **generarMatriz(int height, int weight);

    // FUNCION PRINCIPAL
int main(){
    Neurona and, or, not; // Declarando las neuronas
    int op;
    double *x = (double*)malloc(sizeof(double)*2);
    //double ASIGNANDO MEMORIA A LOS ARREGLOS QUE CONTENDRAN LOS PESOS DE LAS ENTRADAS
    and.w = (double*)malloc(sizeof(double)*2);
    or.w = (double*)malloc(sizeof(double)*2);
    not.w = (double*)malloc(sizeof(double));
    iniciarNeuronas(&and, &or, &not); // Inicializando los valores de las neuronas
    double **datasetNot = get_training_data("NOT", 50);
    double **datasetAND = get_training_data("AND", 50);
    double **datasetOR = get_training_data("OR", 50);
    entrenarNeuronaNot(&not, datasetNot);
    entrenarNeurona(&and, datasetAND);
    entrenarNeurona(&or, datasetOR);
    do{
        system("clear");
        printf("1.-and\n2.-or\n3.-not\n4.-salir\nElegir una opcion: ");
        scanf("%d", &op);
        switch (op){
        case 1:
            for(int i = 0; i < 2; i++){
                printf("Ingresar entrada numero %d-> ", i);
                scanf("%le", &(x[i]));
            }
            printf("El resultado es %d\n", activacion(sumatoria(x, and)));
            break;
        case 2:
            for(int i = 0; i < 2; i++){
                printf("Ingresar entrada numero %d-> ", i);
                scanf("%le", &(x[i]));
            }
            printf("El resultado es %d\n", activacion(sumatoria(x, or)));
            break;
        case 3:
            printf("Ingresar entrada: ");
            scanf("%le", &(x[0]));
            x[1] = 0;
            printf("El resultado es %d\n", activacion(not.w[0] * x[0] + not.bias));
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
double sumatoria(double x[], Neurona n){
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
    or->w[0] = randfrom(0, 1);
    or->w[1] = randfrom(0, 1);
    or->bias = randfrom(0, 1);
    not->w[0] = randfrom(0, 1);
    not->w[1] = 0;
    not->bias = randfrom(0, 1);
}

/* * Funcion de activacion de las neuronas.
   * @param double sum recibe el resultado de la sumatoria para determinar la activacion o no de la neurona.
*/
int activacion(double sum){
    return sum >= 0;
}
double randfrom(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void entrenarNeurona(Neurona* neuron, double** training_data){
    FILE* Arch = fopen("neuronas.dat", "wt");
    int epochs = 10000;
    int counter = 0;
    double salida, error;
    double sum = 0, lr = 0.1;
    for(int i = 0; i < epochs; i++){
        if(counter == 50)
            counter = 0;   
        error = training_data[counter][2] - sumatoria(training_data[counter], *neuron);
        for(int k = 0; k < 2; k++){
            neuron->w[k] += lr * error * training_data[counter][k]; 
        }
        neuron->bias += error * lr;
        fprintf(Arch, "%f %f\n", neuron->w[0], error - neuron->w[0]);
        counter++;
    }   
    fprintf(Arch, "%f, %f, %f\n", neuron->w[0], neuron->w[1], neuron->bias);
    fclose(Arch);
}

void entrenarNeuronaNot(Neurona *neuron, double** training_data){
    FILE *Arch = fopen("not/peso1.dat", "wt");
    int epochs = 100000;
    int counter = 0;
    double salida, error;
    double sum = 0, lr = 0.01;
    for (int i = 0; i < epochs; i++){
        if (counter == 50)
            counter = 0;
        error = training_data[1][counter] - (neuron->w[0] * training_data[0][counter] + neuron->bias);
        neuron->w[0] += lr * error * training_data[0][counter];
        neuron->bias += error * lr;
        fprintf(Arch, "%f, %f\n", neuron->w[0], error);
        counter++;
    }
    fprintf(Arch, "Recta: %f, %f\n", neuron->w[0], neuron->bias);
    fclose(Arch);
}
double **get_training_data(char* gate, int numberOfPoints){
    double dato, dato2, resultado;
    double **matriz;
    FILE* file, *file2;
    if(!strcmp("NOT", gate)){
        matriz = generarMatriz(numberOfPoints, 2);
        file = fopen("not/verdadero.dat", "wt");
        file2 = fopen("not/falso.dat", "wt");
        for(int i = 0; i < numberOfPoints; i++){
            dato = randfrom(-3, 3);
            if(dato <= 0){
                resultado = 1;
                fprintf(file, "%f, %f\n", dato, resultado);
            }else{
                resultado = -1;
                fprintf(file2, "%f, %f\n", dato, resultado);
            }  
            matriz[0][i] = dato;
            matriz[1][i] = resultado;
        }
        fclose(file);
        fclose(file2);
    }
    if(!strcmp("AND", gate)){
        matriz = generarMatriz(3, numberOfPoints);
        file = fopen("and/verdadero.dat", "wt");
        file2 = fopen("and/falso.dat", "wt");
        for(int i = 0; i < numberOfPoints; i++){
            dato = randfrom(-3, 3);
            dato2 = randfrom(-3, 3);
            if(dato > 0 && dato2 > 0){
                resultado = 1;
                fprintf(file, "%f, %f, %f\n", dato, dato2, resultado);
            }else{
                resultado = -1;
                fprintf(file2, "%f, %f, %f\n", dato, dato2, resultado);
            }  
            matriz[i][0] = dato;
            matriz[i][1] = dato2;
            matriz[i][2] = resultado;
        }
        fclose(file);
        fclose(file2);
    }
    if(!strcmp("OR", gate)){
        matriz = generarMatriz(3, numberOfPoints);
        file = fopen("or/falso.dat", "wt");
        file2 = fopen("or/verdadero.dat", "wt");
        for(int i = 0; i < numberOfPoints; i++){
            dato = randfrom(-3, 3);
            dato2 = randfrom(-3, 3);
            if(dato <= 0 && dato2 <= 0){
                resultado = -1;
                fprintf(file, "%f, %f, %f\n", dato, dato2, resultado);
            }else{
                resultado = 1;
                fprintf(file2, "%f, %f, %f\n", dato, dato2, resultado);
            }  
            matriz[i][0] = dato;
            matriz[i][1] = dato2;
            matriz[i][2] = resultado;
        }
        fclose(file);
        fclose(file2);
    }
    return matriz;
}

double** generarMatriz(int height, int weight){
    double** matriz = (double**)malloc(sizeof(double*) * weight);
    for(int i = 0; i < weight; i++)
        matriz[i] = (double*)malloc(sizeof(double) * height);
    return matriz;
}