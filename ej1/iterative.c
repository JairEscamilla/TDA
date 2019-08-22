#include <stdio.h>
#include <time.h>
int main(){
  clock_t start, stop;
  double time;
  unsigned long t;
  FILE* fp = fopen("iterative.dat", "at");
  int counter = 0;
  int n = 0, num;
  int init = 0, second = 1;
  printf("Ingresa n: ");
  scanf("%d", &n);
  printf("0, 1, ");
  start = clock();
  while(init <= n){
    num = init + second;
    printf("%d, ", num);
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
