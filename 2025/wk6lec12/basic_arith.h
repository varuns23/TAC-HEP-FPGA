#ifndef _BASIC_ARITH_H_
#define _BASIC_ARITH_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>


#define N 9

typedef char      dinA_t;
typedef short     dinB_t;
typedef int       dinC_t;
typedef long long dinD_t;

typedef int          dout1_t;
typedef unsigned int dout2_t;
typedef int32_t      dout3_t;
typedef int64_t      dout4_t;

void basic_arith(
     dinA_t inA,
     dinB_t inB,
     dinC_t inC,
     dinD_t inD,
     dout1_t *out1,
     dout2_t *out2,
     dout3_t *out3,
     dout4_t *out4
    );

#endif