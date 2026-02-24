#include <stdio.h>
#include "example.h"


dataOUT_t ref(dataIN_t x[N], dataIN_t h[N]) {
    dataOUT_t acc = 0;
    for (size_t i = 0; i < N; i++) {
        acc += x[i] * h[i];
    }
    return acc;
}

int main(){


  dataIN_t x[N], h[N];
  dataOUT_t result_hw, result_sw;

  srand(time(0));
  for (size_t i = 0; i < N; i++) {
    x[i] = rand() % 10;
    h[i] = rand() % 8;
  }

  example(x, h, result_hw);

  result_sw = ref(x, h);



// Compare the results file with the reference file 
  if (result_sw != result_hw) {
      printf("Test failed  !!!\n");
  } else {
      printf("Test passed !\n");
  }
 
  // Return 0 if the test passes
  return 0;

}

  


