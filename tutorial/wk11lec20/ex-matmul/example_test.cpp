#include "example.h"

int main() {
    din_t A[N][N], B[N], C[N];

    // Initialize A and B
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            A[i][j] = i + j + 1;
            B[i] = (i) * (j+1);
        }
    }

    // Call matrix multiplication
    example(A, B, C);

    // Prdin_t result
    cout << "Result Matrix C:" << endl;
    for (size_t i = 0; i < N; i++) {
            cout << C[i] << " "<<endl;
    }

    return 0;
}
