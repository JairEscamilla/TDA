#include <stdio.h>
#include <time.h>
int main(){
  clock_t start, stop;
  double time;
  unsigned long t;
  FILE* fp = fopen("iterative.csv", "at");
  int counter = 0;
  long long int init = 0, second = 1, num;
  int n = 0;
  printf("Ingresa n: ");
  scanf("%d", &n);
  printf("0, 1, ");
  start = clock();
  while(init <= n){
    num = init + second;
    printf("%lld, ", num);
    init = second;
    second = num;
    stop = clock();
    time = (double)(stop-start)/ CLOCKS_PER_SEC;
    fprintf(fp, "%d, %f\n", counter, time);
    counter++;
  }

  fclose(fp);
  printf("\n");
  return 0;
}
