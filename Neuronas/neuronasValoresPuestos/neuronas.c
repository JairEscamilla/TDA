#include<stdio.h>
#include<stdlib.h>

typedef struct Neuronas{
    double* w;
    double bias;
}Neurona;

double sumatoria(int x[], Neurona n);
int activacion(double sum);

int main(){
    Neurona and, or, not;
    int op;
    int *x = (int*)malloc(sizeof(int)*2);
    and.w = (double*)malloc(sizeof(double)*2);
    or.w = (double*)malloc(sizeof(double)*2);
    not.w = (double*)malloc(sizeof(double)*2);
    and.w[0] = 0.7;
    and.w[0] = 0.3;
    and.bias = -1;
    or.w[0] = 1.61;
    or.w[0] = 0.41;
    or.bias = 2.02;
    not.w[0] = -1.2;
    not.w[0] = 0;
    not.bias = 1;
    do{
        printf("1.- and\n2.-or\n3.-not\n4.-salir");
        scanf("%d", &op);
        switch (op){
        case 1:
            printf("Ingresar datos: ");
            for(int i = 0; i < 2; i++)
                scanf("%d", &(x[i]));
            printf("El resultado es %d\n", activacion(sumatoria(x, and)));
            break;
        case 2:
            printf("Ingresar datos: ");
            for(int i = 0; i < 2; i++)
                scanf("%d", &(x[i]));
            printf("El resultado es %d\n", activacion(sumatoria(x, or)));
            break;
        case 3:
            printf("Ingresar datos: ");
            for(int i = 0; i < 2; i++)
                scanf("%d", &(x[i]));
            printf("El resultado es %d\n", activacion(sumatoria(x, not)));
            break;
        default:
            break;
        }
    } while (op != 4);
    
}   

double sumatoria(int x[], Neurona n){
    double sum = 0;
    for(int i = 0; i < 2; i++)
        sum+= x[i]*n.w[i];
    return sum + n.bias; 
}
int activacion(double sum){
    return sum >= 0;
}