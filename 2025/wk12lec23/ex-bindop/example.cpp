#include "example.h"

//finite Impulse Response (FIR) filter
void example(dataIN_t x[N], dataIN_t h[N], dataOUT_t &y) {
  dataOUT_t prod = 0;    
  dataOUT_t acc = 0;
#pragma HLS INLINE off
#pragma HLS bind_op op=mul impl=DSP variable=prod
#pragma HLS pipeline

 for (size_t i = 0; i < N; i++) {
    prod = x[i] * h[i];
    acc += prod;
  }
  y = acc;
}
