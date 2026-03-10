#include <stdio.h>
#include <math.h>
#include "func_ex2.h"
#include <cstdlib>

int main()
{
  const int samples = 600;
  FILE *oFile;

  int inp, output;
  int coef[N] = { 0, -10, -9, 23, 56, 63, 56, 23, -9, -10, 0};

  int i, rmp;
  inp = 0;
  rmp = 1;

  oFile = fopen("func_ex2_out.dat", "w");
  for (i = 0; i <= samples; i++)
  {
    if (rmp == 1)
      inp = inp + 1;
    else
      inp = inp - 1;

    // Execute the function with latest input
    func_ex2(&output, coef, inp);

    if ((rmp == 1) && (inp >= 75))
      rmp = 0;
    else if ((rmp == 0) && (inp <= -75))
      rmp = 1;

    // Save the results.
    fprintf(oFile, "%i %d %d\n", i, inp, output);
  }
  fclose(oFile);

  printf("Comparing against output data \n");
  if (system("diff -w func_ex2_out.dat func_ex2_ref_out.dat"))
  {

    fprintf(stdout, "*******************************************\n");
    fprintf(stdout, "FAIL: Output DOES NOT match the reference output\n");
    fprintf(stdout, "*******************************************\n");
    return 1;
  }
  else
  {
    fprintf(stdout, "*******************************************\n");
    fprintf(stdout, "PASS: The output matches the reference output!\n");
    fprintf(stdout, "*******************************************\n");
    return 0;
  }
}
