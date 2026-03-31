#include <hls_stream.h>

void read_data(int in[8], hls::stream<int> &s) {
    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        s.write(in[i]);
    }
}

void process_data(hls::stream<int> &s_in, hls::stream<int> &s_out) {
    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        int val = s_in.read();
        s_out.write(val * 2);
    }
}

void write_data(hls::stream<int> &s, int out[8]) {
    for (int i = 0; i < 8; i++) {
#pragma HLS PIPELINE
        out[i] = s.read();
    }
}

void top(int in[8], int out[8]) {
#pragma HLS DATAFLOW

    hls::stream<int> s1, s2;

    read_data(in, s1);
    process_data(s1, s2);
    write_data(s2, out);
}
