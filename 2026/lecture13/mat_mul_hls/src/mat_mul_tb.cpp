//  Test strategy:
//    Test 1 - Identity matrix x any matrix   -> same matrix
//    Test 2 - All-ones matrices              -> each output = INNER_DIM (16)
//    Test 3 - Saturation check                -> max x max accumulated K times
//    Test 4 - Random matrices with reference  -> golden model comparison
//
//  Return value: 0 = PASS, non-zero = FAIL
// =============================================================================

#include "mat_mul.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

// ---------------------------------------------------------------------------
// Reference (software) matrix multiply – golden model
//   C = A * B  (no saturation – we compare raw accumulated values first,
//               then apply the same saturate_cast logic for comparison)
// ---------------------------------------------------------------------------
static void ref_matmul(
    const short a[OUTPUT_ROWS][INNER_DIM],
    const short b[INNER_DIM][OUTPUT_COLS],
    int         c[OUTPUT_ROWS][OUTPUT_COLS])
{
    for (int i = 0; i < OUTPUT_ROWS; i++)
        for (int j = 0; j < OUTPUT_COLS; j++) {
            int sum = 0;
            for (int k = 0; k < INNER_DIM; k++)
                sum += (int)a[i][k] * (int)b[k][j];
            c[i][j] = sum;
        }
}

// ---------------------------------------------------------------------------
// Saturate reference result to match hardware saturate_cast
// ---------------------------------------------------------------------------
static short ref_saturate(int x)
{
    if (x >  32767) return  32767;
    if (x < -32768) return -32768;
    return (short)x;
}

// ---------------------------------------------------------------------------
// Pack a matrix into an AXI-Stream FIFO (row-major order)
// ---------------------------------------------------------------------------
static void pack_stream(
    const short mat[OUTPUT_ROWS][INNER_DIM],
    axis_stream_t& strm,
    int rows, int cols)
{
    int total = rows * cols;
    int idx   = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            axis_pkt_t pkt;
            pkt.data = mat[i][j];
            pkt.keep = 0xFF;
            pkt.last = (ap_uint<1>)((++idx == total) ? 1 : 0);
            strm.write(pkt);
        }
    }
}

// Helper: pack INNER_DIM×OUTPUT_COLS b-matrix
static void pack_b_stream(
    const short mat[INNER_DIM][OUTPUT_COLS],
    axis_stream_t& strm)
{
    int total = INNER_DIM * OUTPUT_COLS;
    int idx   = 0;
    for (int i = 0; i < INNER_DIM; i++) {
        for (int j = 0; j < OUTPUT_COLS; j++) {
            axis_pkt_t pkt;
            pkt.data = mat[i][j];
            pkt.keep = 0xFF;
            pkt.last = (ap_uint<1>)((++idx == total) ? 1 : 0);
            strm.write(pkt);
        }
    }
}

// ---------------------------------------------------------------------------
// Drain output stream and check against golden reference
// ---------------------------------------------------------------------------
static int check_output(
    axis_stream_t& strm_c,
    const int      golden[OUTPUT_ROWS][OUTPUT_COLS],
    const char*    test_name)
{
    int errors = 0;
    for (int i = 0; i < OUTPUT_ROWS; i++) {
        for (int j = 0; j < OUTPUT_COLS; j++) {
            axis_pkt_t pkt = strm_c.read();
            short hw_val   = (short)pkt.data;
            short ref_val  = ref_saturate(golden[i][j]);

            if (hw_val != ref_val) {
                printf("[%s] MISMATCH at [%d][%d]: HW=%d  REF=%d\n",
                       test_name, i, j, (int)hw_val, (int)ref_val);
                errors++;
            }
        }
    }
    if (errors == 0)
        printf("[%s] PASS (%d outputs checked)\n",
               test_name, OUTPUT_ROWS * OUTPUT_COLS);
    else
        printf("[%s] FAIL (%d errors)\n", test_name, errors);

    return errors;
}

// =============================================================================
// MAIN
// =============================================================================
int main()
{
    int total_errors = 0;

    // Dummy control port  (not exercised in C-simulation)
    volatile ap_uint<32> ctrl = 1;

    // =========================================================================
    // Test 1: Identity × Ramp  (A=I, B=ramp)  → C must equal B
    // =========================================================================
    {
        axis_stream_t strm_a, strm_b, strm_c;

        short a[OUTPUT_ROWS][INNER_DIM] = {0};
        short b[INNER_DIM][OUTPUT_COLS];
        int   ref[OUTPUT_ROWS][OUTPUT_COLS];

        // Build identity-ish (OUTPUT_ROWS × INNER_DIM, identity on the square part)
        for (int i = 0; i < OUTPUT_ROWS; i++)
            if (i < INNER_DIM)
                a[i][i] = 1;

        // Ramp values for B
        for (int i = 0; i < INNER_DIM; i++)
            for (int j = 0; j < OUTPUT_COLS; j++)
                b[i][j] = (short)(i * OUTPUT_COLS + j + 1);

        // Golden reference
        ref_matmul(a, b, ref);

        // Drive DUT
        pack_stream(a, strm_a, OUTPUT_ROWS, INNER_DIM);
        pack_b_stream(b, strm_b);

        mat_mul(strm_a, strm_b, strm_c, ctrl);

        total_errors += check_output(strm_c, ref, "Test1-Identity");
    }

    // =========================================================================
    // Test 2: All-ones
    //   Every output element should equal INNER_DIM (= 16), well within 16-bit
    // =========================================================================
    {
        axis_stream_t strm_a, strm_b, strm_c;

        short a[OUTPUT_ROWS][INNER_DIM];
        short b[INNER_DIM][OUTPUT_COLS];
        int   ref[OUTPUT_ROWS][OUTPUT_COLS];

        for (int i = 0; i < OUTPUT_ROWS; i++)
            for (int k = 0; k < INNER_DIM; k++)
                a[i][k] = 1;

        for (int k = 0; k < INNER_DIM; k++)
            for (int j = 0; j < OUTPUT_COLS; j++)
                b[k][j] = 1;

        ref_matmul(a, b, ref);   // every ref[i][j] = INNER_DIM = 16

        pack_stream(a, strm_a, OUTPUT_ROWS, INNER_DIM);
        pack_b_stream(b, strm_b);

        mat_mul(strm_a, strm_b, strm_c, ctrl);

        total_errors += check_output(strm_c, ref, "Test2-AllOnes");
    }

    // =========================================================================
    // Test 3: Saturation
    //   Fill A and B with 32767 (INT16_MAX) – accumulated product overflows
    //   int32 near K*32767*32767 = 16 * ~1e9 ≈ 1.7e10 > INT32_MAX → saturate
    //   The golden model applies the same saturate, so outputs should match.
    // =========================================================================
    {
        axis_stream_t strm_a, strm_b, strm_c;

        short a[OUTPUT_ROWS][INNER_DIM];
        short b[INNER_DIM][OUTPUT_COLS];
        int   ref[OUTPUT_ROWS][OUTPUT_COLS];

        for (int i = 0; i < OUTPUT_ROWS; i++)
            for (int k = 0; k < INNER_DIM; k++)
                a[i][k] = 32767;

        for (int k = 0; k < INNER_DIM; k++)
            for (int j = 0; j < OUTPUT_COLS; j++)
                b[k][j] = 32767;

        // Reference (NOTE: plain int can hold 16 × 32767² ≈ 1.72e10 < 2^31 – OK)
        ref_matmul(a, b, ref);

        pack_stream(a, strm_a, OUTPUT_ROWS, INNER_DIM);
        pack_b_stream(b, strm_b);

        mat_mul(strm_a, strm_b, strm_c, ctrl);

        total_errors += check_output(strm_c, ref, "Test3-Saturation");
    }

    // =========================================================================
    // Test 4: Pseudo-random  (linear congruential, reproducible)
    // =========================================================================
    {
        axis_stream_t strm_a, strm_b, strm_c;

        short a[OUTPUT_ROWS][INNER_DIM];
        short b[INNER_DIM][OUTPUT_COLS];
        int   ref[OUTPUT_ROWS][OUTPUT_COLS];

        unsigned int lfsr = 0xDEADBEEFu;
        auto rand16 = [&]() -> short {
            lfsr ^= lfsr << 13;
            lfsr ^= lfsr >> 17;
            lfsr ^= lfsr << 5;
            return (short)(lfsr & 0x00FF);   // keep values small to avoid overflow
        };

        for (int i = 0; i < OUTPUT_ROWS; i++)
            for (int k = 0; k < INNER_DIM; k++)
                a[i][k] = rand16();

        for (int k = 0; k < INNER_DIM; k++)
            for (int j = 0; j < OUTPUT_COLS; j++)
                b[k][j] = rand16();

        ref_matmul(a, b, ref);

        pack_stream(a, strm_a, OUTPUT_ROWS, INNER_DIM);
        pack_b_stream(b, strm_b);

        mat_mul(strm_a, strm_b, strm_c, ctrl);

        total_errors += check_output(strm_c, ref, "Test4-Random");
    }

    // =========================================================================
    // Result summary
    // =========================================================================
    printf("\n===========================\n");
    if (total_errors == 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("TOTAL ERRORS: %d\n", total_errors);
    printf("===========================\n");

    return total_errors;
}
