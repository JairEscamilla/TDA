#include<stdio.h>
#include<time.h>

typedef struct defNeurona{
    double w[2];
    double bias;
}Neurona;

void iniciarNeurona(Neurona* n1);
void entrenarNeurona(Neurona* n1, int input_training[4][2], int output_training[]);
double sumatoria(Neurona n1, int input_training[4][2], int counter);
int funcionActivacion(double salida);
int prediccion(int x1, int x2, Neurona n1);

int main(){
    Neurona n1;
    int opcion = 0, x1, x2;
    int input_training[4][2] = {
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };
    int output_training[] = {-1, -1, -1, 1};
    iniciarNeurona(&n1);
    entrenarNeurona(&n1, input_training, output_training);
    printf("Pesos: %f, %f, %f\n", n1.w[0], n1.w[1], n1.bias);
    do{
      printf("\n");
      printf("1.-Probar neurona. \n");  
      printf("2.- Salir. \n");
      printf("Ingresar opcion: ");
      scanf("%d", &opcion);
      if(opcion == 1){
          scanf("%d", &x1);
          scanf("%d", &x2);
          printf("El resultado de la prediccion es %d\n", prediccion(x1, x2, n1));
      }
    } while (opcion != 2);
    
    return 0;
}

void iniciarNeurona(Neurona* n1){
    n1->bias = -1;
    n1->w[0] = 1.2;
    n1->w[1] = -1.2;
}

void entrenarNeurona(Neurona *n1, int input_training[4][2], int output_training[]){
    int counter = 0;
    double salida;
    int activacion;
    double learning_rate = 0.5;
    printf("ENTRENANDO NEURONA\n");
    while (counter < 4){
        salida = sumatoria(*n1, input_training, counter);
        activacion = funcionActivacion(salida);
        if (activacion == output_training[counter]){
            printf("PREDICCION CORRECTA\n");
        }else{
            printf("LA PREDICCION HA FALLADO\nRECALCULANDO PESOS\n");
            for(int i = 0; i < 2; i++){
                n1->w[i] = n1->w[i] + learning_rate*output_training[counter]*input_training[counter][i]; 
            }
            counter = -1;
        }
        counter++;
    }
    printf("--------------------------------------------------\nENTRENAMIENTO FINALIZADO\n--------------------------------------------------");
}

double sumatoria(Neurona n1, int input_training[4][2], int counter){
    double sum = 0;
    for(int i = 0; i < 2; i++){
        sum+= n1.w[i]*input_training[counter][i];
    }
    sum+= n1.bias;
    return sum;
}

int funcionActivacion(double salida){
    return salida >= 0? 1: -1;
}

int prediccion(int x1, int x2, Neurona n1){
    double salida = 0;
    salida += n1.w[0]*x1; 
    salida += n1.w[1]*x2;
    salida+= n1.bias;
    return salida >= 0; 
}