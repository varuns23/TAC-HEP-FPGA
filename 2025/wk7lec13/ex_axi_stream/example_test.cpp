#include <hls_stream.h>
#include <stdio.h>

void example(hls::stream<int> &input, hls::stream<int> &output);

int main()
{

   hls::stream<int> input_stream, output_stream;

  int size = 1024;
  int expected_output[size];

//  printf("HLS AXI-Stream no side-channel data example\n");
  //Put data into input
  for(int i=0; i < size; i++){
    input_stream.write(i);
    expected_output[i] = i*2;
  }

  //Call the hardware function
  for(int i=0; i < size; i++){
    example(input_stream, output_stream);
  }


  //Run a software version of the hardware function to validate results
  bool success = true;
  for (int i = 0; i < size; i++) {
    int output_val;
    if (!output_stream.read_nb(output_val)) {
      success = false;
      break;
    }
    if (output_val != expected_output[i]) {
      success = false;
    }
  }


  //Compare results
  if(success){
    printf("Success HW and SW results match\n");
    } else {
      printf("ERROR HW and SW results mismatch\n");
    }
  return 0;
}

  


