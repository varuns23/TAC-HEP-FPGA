#include "basic_arith_ap.h"

void basic_arith_ap(
 dinA_t  inA,
 dinB_t  inB,
 dinC_t  inC,
 dinD_t  inD, 
 dout1_t *out1, 
 dout2_t *out2, 
 dout3_t *out3, 
 dout4_t *out4 ){
 
 // Basic arithmetic & math.h sqrtf()
 *out1 = inA * inB;
 *out2 = inB + inA;
 *out3 = inC / inA;
 *out4 = inD % inA;
}