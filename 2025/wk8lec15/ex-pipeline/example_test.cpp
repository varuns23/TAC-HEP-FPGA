#include <stdio.h>
#include "example.h"


int main()
{
  din_t var[N];
  dout_t total;

  int i, retval = 0;
  ofstream FILE;

  // Create input data
  for (i = 0; i < N; ++i) {
      var[i] = i + ((i+5)*2);
  }
  // Save the results to a file
  FILE.open("result.dat");

  // Call the function
  total = example(var);
  FILE << total << endl;
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

  


