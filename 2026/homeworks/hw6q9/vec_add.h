#ifndef _VEC_ADD_H_
#define _VEC_ADD_H_

#include <ap_int.h>
#define N 15

typedef ap_uint<4> dint16_t;

void vec_add(dint16_t A[N], dint16_t B[N], dint16_t C[N]);


#endif
