#ifndef VIDEO_ACCEL_H
#define VIDEO_ACCEL_H

#include <iostream>
#include <cstdlib>

#include "ap_int.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

//64x64
#define WIDTH  16
#define HEIGHT 16
#define NPIX (WIDTH * HEIGHT)



void video_accel(
    hls::stream<ap_axiu<24,1,1,1>>& in,
    hls::stream<ap_axiu<8,1,1,1>>& out,
    ap_uint<13> threshold
);

void rgb2gray(
    hls::stream<ap_axiu<24,1,1,1>>& in,
    hls::stream<uint8_t>& out);

void filter3x3(
    hls::stream<uint8_t>& in,
    hls::stream<uint8_t>& out);

void thresholding(
    hls::stream<uint8_t>& in, 
    hls::stream<uint8_t>& out,
    ap_uint<13> threshold);


void detect_objects(
    hls::stream<uint8_t>& in,
    hls::stream<ap_axiu<8,1,1,1>>& out);

void sort_objects(ap_uint<13> sizes[16], ap_uint<13> ids[16]);

int mul_example(int a, int b);

#endif