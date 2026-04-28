#include "mat_mul.h"

data_t saturate_cast(acc_t x)
{
    const acc_t MAX_VAL =  (1 << 15) - 1;  //  32767
    const acc_t MIN_VAL = -(1 << 15);       // -32768

    if (x > MAX_VAL) return (data_t) MAX_VAL;
    if (x < MIN_VAL) return (data_t) MIN_VAL;
    return (data_t) x;
}

acc_t dot_product(data_t a_row[INNER_DIM], data_t b_col[INNER_DIM])
{

    acc_t sum = 0;

DOT_LOOP:
    for (int k = 0; k < INNER_DIM; k++)
    {
        sum += (acc_t)a_row[k] * (acc_t)b_col[k];
    }
    return sum;
}

void load_tiles(
    axis_stream_t& strm_a,
    axis_stream_t& strm_b,
    data_t         tile_a[OUTPUT_ROWS][INNER_DIM],
    data_t         tile_b[INNER_DIM][OUTPUT_COLS])
{

LOAD_A:
    for (int i = 0; i < OUTPUT_ROWS; i++) {
        for (int k = 0; k < INNER_DIM; k++) {

            axis_pkt_t pkt = strm_a.read();
            tile_a[i][k] = pkt.data;
        }
    }

LOAD_B:
    for (int k = 0; k < INNER_DIM; k++) {
        for (int j = 0; j < OUTPUT_COLS; j++) {

            axis_pkt_t pkt = strm_b.read();
            tile_b[k][j] = pkt.data;
        }
    }
}

void compute_tile(
    data_t tile_a[OUTPUT_ROWS][INNER_DIM],
    data_t tile_b[INNER_DIM][OUTPUT_COLS],
    acc_t  accum[OUTPUT_ROWS][OUTPUT_COLS])
{

    // Initialize accumulators to zero
INIT_M:
    for (int i = 0; i < OUTPUT_ROWS; i++) {
        for (int j = 0; j < OUTPUT_COLS; j++) {

            accum[i][j] = 0;
        }
    }


MAC_I:
    for (int i = 0; i < OUTPUT_ROWS; i++) {


MAC_J:
        for (int j = 0; j < OUTPUT_COLS; j++) {

MAC_K:
            for (int k = 0; k < INNER_DIM; k++) {

                accum[i][j] += (acc_t)tile_a[i][k] * (acc_t)tile_b[k][j];
            }
        }
    }
}

void store_results(
    acc_t          accum[OUTPUT_ROWS][OUTPUT_COLS],
    axis_stream_t& strm_c)
{

    // #pragma HLS ARRAY_PARTITION variable=accum complete dim=0
    //   (must match the partition in compute_tile – see §4 note)

    int total = OUTPUT_ROWS * OUTPUT_COLS;
    int idx   = 0;

STORE_M:
    for (int i = 0; i < OUTPUT_ROWS; i++) {
STORE_N:
        for (int j = 0; j < OUTPUT_COLS; j++) {

            axis_pkt_t out;
            out.data = saturate_cast(accum[i][j]);
            out.keep = 0xFF;
            out.last = (ap_uint<1>)((++idx == total) ? 1 : 0);
            strm_c.write(out);
        }
    }
}

void mac_tile_dataflow(
    axis_stream_t& strm_a,
    axis_stream_t& strm_b,
    axis_stream_t& strm_c)
{
    // Local tile buffers  (DATAFLOW makes these ping-pong automatically)
    data_t tile_a[OUTPUT_ROWS][INNER_DIM];
    data_t tile_b[INNER_DIM][OUTPUT_COLS];
    acc_t  accum[OUTPUT_ROWS][OUTPUT_COLS];

    load_tiles   (strm_a, strm_b, tile_a, tile_b);
    compute_tile (tile_a, tile_b, accum);
    store_results(accum, strm_c);
}

void mat_mul(
    axis_stream_t&         strm_a,
    axis_stream_t&         strm_b,
    axis_stream_t&         strm_c,
    volatile ap_uint<32>&  ctrl)
{


  // Delegate to DATAFLOW region
    mac_tile_dataflow(strm_a, strm_b, strm_c);
}
