#include "vec_add.h"
#include <iostream>
#include <cstdlib>
#define SIZE N


int main() {

    dint16_t A[SIZE];
    dint16_t B[SIZE];
    dint16_t C[SIZE];

    // Initialize inputs
    for (dint16_t i = 0; i < SIZE; i++) {
        A[i] = i;
        B[i] = 2*i;
    }

    // Call function 
    vec_add(A, B, C);

    // Verify results
    int errors = 0;
    for (dint16_t i = 0; i < SIZE; i++) {
        if (C[i] != A[i] + B[i]) {
	  errors++;
	}

    }

    if (errors == 0)
        std::cout << "TEST PASSED\n";
    else
        std::cout << "TEST FAILED\n";

    return errors;
}

