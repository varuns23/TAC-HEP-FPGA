#include <ap_int.h>
#include <hls_stream.h>

#include "example.h"

// Top-level function for HLS
void example(din_t A[N][N], din_t B[N], din_t C[N]) {

    // Matrix multiplication
  for (size_t i = 0; i < N; i++) {
    float prod = 0;
    for (size_t j = 0; j < N; j++) {

      prod += A[i][j] * B[j];
    }
    C[i] = prod;
  }
  bubble_sort(C);
}


void bubble_sort(din_t arr[SORT_N]) {
#pragma HLS PIPELINE

    for (int i = 0; i < SORT_N - 1; i++) {
        for (int j = 0; j < SORT_N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

