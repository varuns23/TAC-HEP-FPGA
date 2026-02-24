#include <stdio.h>

void example(int a, int b, int *c);

int main()
{

  int a;
  int b;
  int c;
  int d;
  int sw_result;

  printf("HLS AXI-Lite Example\n");
  printf("Function c += a + b\n");
  printf("Initial values a = 5, b = 10, c = 0\n");

  a = 5;
  b = 10;
  c = 0;
  d = 0;

  example(a,b,&c);
  d += a + b;

  printf("HW result = %d\n",c);
  printf("SW result = %d\n",d);

  if(d == c){
    printf("Success SW and HW results match\n");
    return 0;
  }
  else{
    printf("ERROR SW and HW results mismatch\n");
    return 1;
  }
}




