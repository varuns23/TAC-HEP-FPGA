#pragma once
// =============================================================================
//  Matrix-Multiply-Accumulate (MAC) Engine
//  Target  : xcvu13p-fsga2577-2-e  (Virtex UltraScale+)
//  Clock   : 25 ns  (40 MHz)
//  Tool    : Vitis HLS 2024.1
// =============================================================================
//
//  Architecture
//  ============
//  Computes  C[M][N] += A[M][K] * B[K][N]  (integer 16-bit accumulate to 32-bit)
//  One call  processes a single MxK  x  KxN  tile:
//    M = OUTPUT_ROWS  = 8
//    N = OUTPUT_COLS  = 8
//    K = INNER_DIM    = 16
//
#include <hls_stream.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_math.h>

static const int OUTPUT_ROWS = 8;   // M
static const int OUTPUT_COLS = 8;   // N
static const int INNER_DIM   = 16;  // K

typedef ap_int<16>  data_t;       // 16-bit signed input elements
typedef ap_int<32>  acc_t;        // 32-bit signed accumulator
typedef ap_uint<8>  addr_t;       // tile address (fits 0..255)

struct axis_pkt_t {
    data_t  data;   // element value
    ap_uint<1> last; // TLAST – end-of-frame marker
    ap_uint<8> keep; // TKEEP – byte enables (unused here, kept for AXI-S)
};

// ---------------------------------------------------------------------------
// Internal FIFO types between dataflow stages
// ---------------------------------------------------------------------------
typedef hls::stream<axis_pkt_t>  axis_stream_t;
typedef hls::stream<acc_t>       acc_stream_t;

// ---------------------------------------------------------------------------
// Top-level function declaration
// ---------------------------------------------------------------------------
void mat_mul(
    axis_stream_t& strm_a,     // AXI-Stream input: matrix A elements (row-major)
    axis_stream_t& strm_b,     // AXI-Stream input: matrix B elements (row-major)
    axis_stream_t& strm_c,     // AXI-Stream output: matrix C result
    volatile ap_uint<32>& ctrl // AXI-Lite: bit0=start, bit1=done (read back)
);
