#include <cstdlib>
#include "basic_arith_ap.h"

int main() {
    dinA_t inA;
    dinB_t inB;
    dinC_t inC;
    dinD_t inD;
    dout1_t out1;
    dout2_t out2;
    dout3_t out3;
    dout4_t out4;

    int i, retval = 0;
    FILE* fp;

  // Save the results to a file
  fp = fopen("result_basic_arith_ap.dat", "w");

  for (i = 0; i < N; i++) {
      // Create input data
      inA = i + 2;
      inB = i + 23;
      inC = i + 234;
      inD = i + 2345;

      // Call the function to operate on the data
      basic_arith_ap(inA, inB, inC, inD, &out1, &out2, &out3, &out4);

      fprintf(fp, "%d*%d=%d; %d+%d=%d; %d/%d=%d; %d mod %d=%d;\n",
              inA.to_int(), inB.to_int(), out1.to_int(), inB.to_int(),
              inA.to_int(), out2.to_int(), inC.to_int(), inA.to_int(),
              out3.to_int(), inD.to_int(), inA.to_int(), out4.to_int());
//-      fprintf(fp, "%d*%d=%d; %d+%d=%d; %d/%d=%d; %d mod %d=%d;\n",
//-              inA, inB, out1, inB,
//-              inA, out2, inC, inA,
//-              out3, inD, inA, out4);
  }
  fclose(fp);

  // Compare the results file with the reference file 
  retval = system("diff --brief -w result_basic_arith_ap.dat result_basic_arith_ap_ref.dat");
  if (retval != 0) {
      printf("Test failed  !!!\n");
      retval = 1;
  } else {
      printf("Test passed !\n");
  }

  // Return 0 if the test passes
  return retval;
}