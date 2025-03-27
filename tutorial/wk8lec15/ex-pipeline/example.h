#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <fstream>
#include <iostream>

using namespace std;

#include "ap_int.h"
#define N 64

typedef ap_int<7> din_t;
typedef ap_int<10> dout_t;

dout_t example(din_t mem[N]);

#endif
