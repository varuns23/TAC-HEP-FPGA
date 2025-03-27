#include <stdio.h>
#include "example.h"

int main () {

  unsigned int input[N];
  unsigned int temp[N];
  unsigned int output[N];

  short a = 2;
  short b = 3;
  unsigned int c = 5;

  int retval = 0;

  ofstream FILE;
  FILE.open("result.dat");

  for(int irnd=0; irnd<N; irnd++){
    input[irnd] = rand() % 20;
    output[irnd] = 0;
  //  printf("%i, input: %u", irnd, input[irnd]);
  }


  // Execute the function with latest input
  example(input, a, b, c, output);


  // Create input data
  for (int i = 0; i < N; ++i) {
  FILE << i <<" "<<input[i]<<" "<<output[i] << endl;
  }
  // Call the function
  FILE.close();

  // Compare the results file with the golden results
  retval = system("diff --brief -w result.dat result_ref.dat");
  if (retval != 0) {
      printf("Test failed  !!!\n");
      retval = 1;
  } else {
      printf("Test passed !\n");
  }

  // Return 0 if the test passes
  return retval;

}

  


