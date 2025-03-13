#include <stdio.h>

void example(int *input, int *output, int size);

int main()
{
  int size = 256;
  int input[size];
  int output[size];
  int tmp[size];

//  printf("HLS AXI-Stream no side-channel data example\n");
  //Put data into input
  for(int i=0; i < size; i++){
    input[i] = i;
  }

  //Call the hardware function
  example(input,output, size);

  //Run a software version of the hardware function to validate results
  for(int i=0; i < size; i++){
    tmp[i] = input[i] * 2;
  }

  //Compare results
  for(int i=0; i < size; i++){
    if(output[i] != tmp[i]){
      printf("ERROR HW and SW results mismatch\n");
      return 1;
    }
  }
  printf("Success HW and SW results match\n");
  return 0;
}

  


