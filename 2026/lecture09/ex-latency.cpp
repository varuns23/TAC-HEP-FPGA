void latency_example(int a, int b, int &c) {
#pragma HLS LATENCY min=2 max=4

    int temp1 = a + b;
    int temp2 = temp1 * 2;
    c = temp2 + 5;
}
