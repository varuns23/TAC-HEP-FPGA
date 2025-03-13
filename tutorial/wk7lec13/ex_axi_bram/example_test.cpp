#include <stdio.h>

void example(int input[256], int output[256]);

int main()
{
  int i;
  int input[256];
  int output[256];
  int tmp[256];

//  printf("HLS AXI-Stream no side-channel data example\n");
  //Put data into input
  for(i=0; i < 256; i++){
    input[i] = i;
  }

  //Call the hardware function
  example(input,output);

  //Run a software version of the hardware function to validate results
  for(i=0; i < 256; i++){
    tmp[i] = input[i] * 2;
  }

  //Compare results
  for(i=0; i < 256; i++){
    if(output[i] != tmp[i]){
      printf("ERROR HW and SW results mismatch\n");
      return 1;
    }
  }
  printf("Success HW and SW results match\n");
  return 0;
}

  


