#include "video_accel.h"

// Streaming Multi-Stage Video Processing + Object Tagging Accelerator
// This is a pipeline-heavy, dataflow-based design combining
// -  Image filtering
// -  Feature extraction
// -  Object clustering + sorting
// -  Tag generation

// Lets try to implement loop + memory + task + resource pragmas


void video_accel(
    hls::stream<ap_axiu<24,1,1,1>>& in,
    hls::stream<ap_axiu<8,1,1,1>>& out,
    ap_uint<13> threshold
) {

hls::stream<uint8_t> gray, filtered, binary;
ap_axiu<24,1,1,1> pixel = in.read();
hls::stream<uint8_t> 
ap_axiu<8,1,1,1> result; = out.read();

    rgb2gray(pixel, gray);
    filter3x3(gray, filtered);
    thresholding(filtered, binary, threshold);
    detect_objects(binary, out);

}

void rgb2gray(hls::stream<ap_axiu<24,1,1,1>>& in,
              hls::stream<uint8_t>& out) {

    for (ap_uint<13> i = 0; i < NPIX; i++) {

        ap_axiu<24,1,1,1> pix = in.read();
        uint8_t r = pix.data.range(23,16);
        uint8_t g = pix.data.range(15,8);
        uint8_t b = pix.data.range(7,0);

        uint8_t gray = (r + g + b) / 3;
        out.write(gray);
    }
}

void filter3x3(hls::stream<uint8_t>& in,
               hls::stream<uint8_t>& out) {

    uint8_t window[3][3];

    for (ap_uint<13> i = 0; i < NPIX; i++) {


        int sum = 0;

        for (ap_uint<2> i=0;i<3;i++)
            for (ap_uint<2> j=0;j<3;j++)
                sum += window[i][j];

        out.write(sum/9);
    }
}

void thresholding(hls::stream<uint8_t>& in,
                  hls::stream<uint8_t>& out,
                  ap_uint<13> threshold) {


    for (ap_uint<13> i = 0; i < NPIX; i++) {
        uint8_t val = in.read();
        out.write(val > threshold ? 255 : 0);
    }
}

void detect_objects(hls::stream<uint8_t>& in,
                    hls::stream<ap_axiu<8,1,1,1>>& out) {

    uint8_t label_map[HEIGHT][WIDTH];


    for (ap_uint<7> i = 0; i < HEIGHT; i++) {
        for (ap_uint<7> j = 0; j < WIDTH; j++) {


            // simple labeling logic
        }
    }
}

void sort_objects(ap_uint<13> sizes[16], ap_uint<13> ids[16]) {

    for (ap_uint<4> i = 0; i < 16; i++) {
        for (ap_uint<4> j = i+1; j < 16; j++) {
            if (sizes[j] > sizes[i]) {
                std::swap(sizes[i], sizes[j]);
                std::swap(ids[i], ids[j]);
            }
        }
    }
}

int mul_example(ap_uint<13> a, ap_uint<13> b) {
    return a * b;
}
