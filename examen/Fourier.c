/*
* @author:  Allan Jair Escamilla Hernández, Alan Flores Quezada
* @date:    3/octubre/2019
* @file:    Fourier.c
*/
// Incluyo las librerias
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define PI 3.1416 // Defino una constante

// Defino la estructura de datos para la senial
typedef struct defDato{
    double A, f, *t, *tf, tifi, salto; 
    int n, number; 
}Dato;

// Prototipos de las funciones
void leerDatos(Dato* senial);
void decode(Dato senial);
double suma(Dato senial, double t);
void imprimir(Dato senial);
void plot(int n);


// Funcion principal
int main(){
    Dato senial;    // Defino la senial
    leerDatos(&senial); // Mando a llamar a la funcion de lectura de datos
    decode(senial); // Decodifico la senial
    imprimir(senial); // Imprimo en un archivo la senial
    plot(senial.n); // Grafico la senial
    // Liberando memoria
    free(senial.t);
    free(senial.tf);
    return 0;
}

/*  * Funcion que lee los datos
    * @param Dato* senial. Estructura de los datos  a leer.
*/
void leerDatos(Dato* senial){
    int st;
    double salto;
    printf("Ingresar amplitud: ");
    scanf("%lf", &(senial->A));
    printf("Ingresar la frecuencia: ");
    scanf("%lf", &(senial->f));
    printf("Ingresar numero de harmonicos: ");
    scanf("%d", &(senial->n));
    printf("Ingresar el tiempo final: ");
    scanf("%lf", &(senial->tifi));
    printf("Ingresar sizeof(t): ");
    scanf("%d", &st);
    salto = senial->tifi / st;
    senial->t = (double*)malloc(sizeof(double) * st);
    senial->tf = (double*)malloc(sizeof(double) * st);
    senial->salto = salto;
    senial->number = st;
}

/*  * Funcion que decodifica la senial
    * @param Dato senial. Estructura de los datos a trabajar
*/
void decode(Dato senial){
    int j = 0;
    for(double i = 0; i < senial.tifi; i+= senial.salto){
        senial.t[j] = i;
        senial.tf[j] = (senial.A/2) + suma(senial, i);
        j++; 
    }
}


/*  * Funcion que hace la sumatoria de las señales
    * @param Dato senial. Estructura de los datos a trabajar.
    * @param double t. valor de tiempo
*/
double suma(Dato senial, double t){
    double counter = 0;
    for(int n = 1; n < senial.n; n++){
        counter+= -(senial.A/(PI*n))*(cos(PI*n)-1)*(sin(2*PI*n*senial.f*t));
    }
    return counter;
}

/*  * Funcion que imprime en un archivo los datos obtenidos
    * @param Dato senial. Estructura de los datos a trabajar
*/
void imprimir(Dato senial){
    FILE* arch = fopen("senial.txt", "wt");
    for(int i = 0; i < senial.number; i++){
        fprintf(arch, "%lf, %lf\n", senial.t[i], senial.tf[i]);
    }
    fclose(arch);
}

/*  * Funcion que grafica los resultados
    * @param int n. Numero de datos de la lista dinamica
*/
void plot(int n){
  char title[100];
  sprintf(title, "set title \"f(t) con %d armonicos\"", n);
  char * configGnuplot[] = {title,
                                "set ylabel \"f(t)\"",
                                "set xlabel \"t\"",
                                "plot \"senial.txt\" with lines",
                                "set autoscale",
                                "replot"
                               };
  FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
  for (int i=0; i < 4; i++){
    fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
  }
}

// RESPUESTA A LA PREGUNTA EXTRA: Al ir aumentando el valor de n, disminuia la frecuencia al momento de realizar la grafica y la senial era mas amplia