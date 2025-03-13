void example(int input[256], int output[256]) {
    #pragma HLS INTERFACE bram port=input
    #pragma HLS INTERFACE bram port=output
    #pragma HLS INTERFACE s_axilite port=return

    for (int i = 0; i < 256; i++) {
        output[i] = input[i] * 2;
    }
}

