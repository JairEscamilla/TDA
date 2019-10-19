#include<stdio.h>
#include<stdlib.h>

typedef struct Neuronas{
    double* w;
    double bias;
}Neurona;

double sumatoria(int x[], Neurona n);
int activacion(double sum);
void iniciarNeuronas(Neurona* and, Neurona* or, Neurona* not);

int main(){
    Neurona and, or, not;
    int op;
    int *x = (int*)malloc(sizeof(int)*2);
    and.w = (double*)malloc(sizeof(double)*2);
    or.w = (double*)malloc(sizeof(double)*2);
    not.w = (double*)malloc(sizeof(double)*2);
    iniciarNeuronas(&and, &or, &not);
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
    
}   

double sumatoria(int x[], Neurona n){
    double sum = 0;
    for(int i = 0; i < 2; i++)
        sum+= x[i]*n.w[i];
    return sum + n.bias; 
}

void iniciarNeuronas(Neurona* and, Neurona* or, Neurona* not){
    and->w[0] = 1;
    and->w[1] = 1;
    and->bias = -1;
    or->w[0] = 1;
    or->w[1] = 1;
    or->bias = 0;
    not->w[0] = -1;
    not->w[1] = 0;
    not->bias = 0.75;
}

int activacion(double sum){
    return sum >= 0.5;
}