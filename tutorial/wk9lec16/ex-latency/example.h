#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#define N 60

void example (
  unsigned int in[N],
  short a,
  short b,
  unsigned int c,
  unsigned int out[N]
  );

unsigned int squared(unsigned int );


unsigned int func(short a, short b);
#endif
