#include <ap_int.h>

void mul_example(int a[8], int b[8], int c[8]) {
#pragma HLS ALLOCATION instances=mul limit=2 operation

    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        c[i] = a[i] * b[i];
    }
}
