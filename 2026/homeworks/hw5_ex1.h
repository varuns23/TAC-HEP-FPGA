#ifndef _HW5_EX1_H_
#define _HW5_EX1_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#define N 30

void read_data(int *in_r, int *out_r);
void compute_blur(int *in_c, int *out_c);
void write_data(int *in_w, int *out_w);
void hw5_ex1(int *A, int *B);

#endif
