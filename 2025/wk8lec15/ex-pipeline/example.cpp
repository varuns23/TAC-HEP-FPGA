#include "example.h"

dout_t example(din_t mem[N]) {
    
    dout_t total = 0;

    for (int i = 2; i < N; ++i){

        #pragma HLS pipeline II=2
    
        total += mem[i] + mem[i - 1] + mem[i - 2];
    }
    return total;
}
