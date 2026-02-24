#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ap_int.h"

using namespace std;

#define N 16

typedef ap_int<4> dataIN_t;
typedef ap_int<8> dataOUT_t;

void example(dataIN_t x[N], dataIN_t h[N], dataOUT_t &y);


#endif
