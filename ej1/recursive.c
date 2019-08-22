#include<stdio.h>
#include<time.h>

void fibo(long long int init, long long int second, int n, int counter, clock_t start);

int main(){
  int n;
  clock_t start;
  printf("Ingresa n: ");
  scanf("%d", &n);
  printf("0, 1, ");
  start = clock();
  fibo(0, 1, n - 2, 0, start);
  printf("\n");
  return 0;
}

void fibo(long long int init, long long int second, int n, int counter, clock_t start){
   if(init <= n){
     clock_t  stop;
     FILE* fp = fopen("recursive.csv", "at");
     long long int numero = init + second;
     printf("%lld, ", numero);
     init = second;
     second = numero;
     stop = clock();
     fprintf(fp, "%d, %f\n", counter, (double) (stop - start) /  CLOCKS_PER_SEC);
     fclose(fp);
     fibo(init, second, n, counter+1, start);
   }
}
