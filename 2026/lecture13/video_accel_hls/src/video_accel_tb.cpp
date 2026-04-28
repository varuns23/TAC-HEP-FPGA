#include "video_accel.h"


int main() {
    hls::stream<ap_axiu<24,1,1,1>> in;
    hls::stream<ap_axiu<8,1,1,1>> out;

    // Generate synthetic image
    for (int i = 0; i < NPIX; i++) {
        ap_axiu<24,1,1,1> pix;
        pix.data = rand();
        in.write(pix);
    }

    video_accel(in, out, 128);

    while (!out.empty()) {
        auto val = out.read();
        std::cout << (int)val.data << std::endl;
    }

    return 0;
}
