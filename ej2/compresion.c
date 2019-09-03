#include <stdio.h>
#include <stdlib.h>

void obtenerNumeros(int num, int pos);

int main(int argc, char const *argv[]) {
  int numero;
  int nn = 0;
  for(int i = 1; i < argc; i++){
    numero = atoi(argv[i]);
    if(numero >= 0 && numero <= 16){
      numero <<=4;
      nn = nn | numero;
    }
  }
  obtenerNumeros(nn, 1);
  return 0;
}

void obtenerNumeros(int num, int pos){
  num <<= 4*pos;
  num = num | pos;
  printf("%d\n", num);
}
