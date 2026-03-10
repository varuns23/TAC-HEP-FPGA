#define N 16

void test_func_v2(float x[N], float a, float b, float c, float y[N]) {

    for (int i = 0; i < N; i++) {

        y[i] = x[i] * a + b + c;

    }
}
