#include <ap_int.h>

#define N 16

typedef ap_int<16> data_t;
typedef ap_int<32> acc_t;

void test_func_optimized(data_t x[N],
                           data_t a,
                           data_t b,
                           data_t c,
                           acc_t y[N]) {

#pragma HLS INTERFACE s_axilite port=a
#pragma HLS INTERFACE s_axilite port=b
#pragma HLS INTERFACE s_axilite port=c
#pragma HLS INTERFACE s_axilite port=return

#pragma HLS INTERFACE m_axi port=x offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=y offset=slave bundle=gmem

    for (int i = 0; i < N; i++) {

#pragma HLS PIPELINE II=1

        acc_t temp;

        temp = (acc_t)x[i] * a;
        temp = temp + b;
        temp = temp + c;

        y[i] = temp;
    }
}
