void stable_example(int in[8], int out[8], int scale) {
#pragma HLS STABLE variable=scale

    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        out[i] = in[i] * scale;
    }
}
