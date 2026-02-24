void example(int a, int b, int *c) {
//    #pragma HLS INTERFACE s_axilite port=a
//    #pragma HLS INTERFACE s_axilite port=b
//    #pragma HLS INTERFACE s_axilite port=c
//    #pragma HLS INTERFACE s_axilite port=return
    #pragma HLS INTERFACE m_axi port=a
    #pragma HLS INTERFACE m_axi port=b
    #pragma HLS INTERFACE m_axi port=c
    #pragma HLS INTERFACE m_axi port=return

    *c = a + b;
}
