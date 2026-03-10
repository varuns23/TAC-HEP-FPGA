#include <iostream>
#include <cmath>

#define N 16

using namespace std;

// Function prototypes
void test_func(float x[N], float a, float b, float c, float y[N]);
//void test_func_v2(float x[N], float a, float b, float c, float y[N]);
//void test_func_optimized(float x[N], float a, float b, float c, float y[N]);

int main() {

    float x[N];
    float y_basic[N];
    float y_basic_v2[N];

    float y_opt[N];

    float a = 3.0;
    float b = 4.0;
    float c = 5.0;

    // Initialize input array
    for (int i = 0; i < N; i++) {
        x[i] = i;
    }

    test_func(x, a, b, c, y_basic);
    //test_func_v2(x, a, b, c, y_basic_v2);
    //test_func_optimized(x, a, b, c, y_opt);

    // Verify results
    int errors = 0;

    for (int i = 0; i < N; i++) {

        float expected = x[i] * a + b + c;

        cout << "i=" << i
             << " Expected=" << expected
             << " Basic=" << y_basic[i]
             << " Opt=" << y_opt[i]
             << endl;

        if (fabs(expected - y_basic[i]) > 1e-6) {
            errors++;
        }
    }

    if (errors == 0)
        cout << "TEST PASSED ✅" << endl;
    else
        cout << "TEST FAILED ❌" << endl;

    return 0;
}
