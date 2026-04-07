#include "vec_add.h"

void vec_add(dint16_t A[N], dint16_t B[N], dint16_t C[N]) {
    for (dint16_t i = 0; i < N; i++) {
        #pragma HLS UNROLL
        C[i] = A[i] + B[i];
	
    }
}
