#include "example.h"
#include <cstdlib>  // For rand() and srand()
#include <cassert>  // For assertions
#include <stdio.h>


void get_randoms(int *arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    arr[i] = (rand() % 500) + 1;  // Generate numbers between 1 and 500
  }
}

void get_expected(int *temp_in, int *temp_out){
  for(size_t i = 1; i<N-1; i++)
    temp_out[i] = (temp_in[i-1] + temp_in[i] + temp_in[i+1])/3;
}

int main () {

  int input[N];
  int temp[N];
  int output[N];
  for (size_t i = 0; i < N; ++i) {
    temp[i]=0;
    output[i]=0;
  }

  get_randoms(input, N);

  example(input, output);
  get_expected(input, temp);

  int retval = 0;

  ofstream FILE;
  FILE.open("result.dat");

  // Create input data
  for (size_t i = 0; i < N; ++i) {
    cout<<input[i]<<" "<<output[i]<<" "<<temp[i]<<endl;
    FILE << i <<" "<<input[i]<<" "<<output[i] << endl;
  }
  // Call the function
  FILE.close();

  // Compare the results file with the golden results
  for (size_t i = 0; i < N; ++i) {
    if(output[i] != temp[i])
      retval=1;
  }

  if (retval != 0) {
    printf("Test failed  !!!\n");
    retval = 1;
  } else {
    printf("Test passed !\n");
  }

  // Return 0 if the test passes
  return retval;

}
