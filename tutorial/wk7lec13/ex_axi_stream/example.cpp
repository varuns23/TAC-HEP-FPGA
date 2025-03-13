#include <hls_stream.h>

void example(hls::stream<int> &input, hls::stream<int> &output) {
    #pragma HLS INTERFACE axis port=input
    #pragma HLS INTERFACE axis port=output
    #pragma HLS INTERFACE ap_ctrl_none port=return

    int data;
    if (input.read_nb(data)) { // Non-blocking read
        output.write(data * 2);
    }
}

