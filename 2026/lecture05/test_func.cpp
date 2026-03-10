#define N 16

void test_func(float x[N], float a, float b, float c, float y[N]) {

    for (int i = 0; i < N; i++) {
        double temp;

        temp = x[i] * a;
        temp = temp + b;
        temp = temp + c;

        y[i] = temp;
    }
}
