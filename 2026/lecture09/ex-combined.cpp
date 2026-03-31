void combined(int in[8], int out[8], int scale) {
#pragma HLS DATAFLOW
#pragma HLS STABLE variable=scale

    hls::stream<int> s1, s2;

    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        s1.write(in[i]);
    }

    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        int tmp = s1.read() * scale;
        s2.write(tmp);
    }

    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        out[i] = s2.read();
    }
}
