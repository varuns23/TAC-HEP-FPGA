void example(int *input, int *output, int size) {
    #pragma HLS INTERFACE m_axi port=input depth=1024
    #pragma HLS INTERFACE m_axi port=output depth=1024
    #pragma HLS INTERFACE s_axilite port=size
    #pragma HLS INTERFACE s_axilite port=return


    for (int i = 0; i < size; i++) {
        output[i] = input[i] * 2;
    }
}

