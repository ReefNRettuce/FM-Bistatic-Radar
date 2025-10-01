#include "fir_filter.h"

// Define the data types we'll use in our design.
// Using custom types makes it easy to change precision later.
typedef int data_t;
typedef int acc_t;

// This is the top-level function that Vitis HLS will synthesize into an FPGA circuit.
void fir_filter(
    data_t *output, // Pointer to where the output result will be stored
    data_t input    // The single input data sample
) {
    // This pragma tells HLS to map the function arguments to specific hardware interfaces.
    // 's_axilite' creates a simple, low-speed control interface.
    // 'ap_ctrl_none' means we don't need start/done/idle signals.
    #pragma HLS INTERFACE s_axilite port=return bundle=control
    #pragma HLS INTERFACE s_axilite port=output bundle=control
    #pragma HLS INTERFACE s_axilite port=input bundle=control

    // This is the shift register that forms the tapped delay line of the filter.
    // Declaring it 'static' tells HLS to create registers that hold their state
    // between each call to this function. This is the hardware memory.
    static data_t shift_reg[N_TAPS] = {0};

    // This pragma tells HLS to pipeline the main processing loop.
    // Pipelining allows a new input sample to be processed every clock cycle,
    // dramatically increasing the throughput of our filter.
    #pragma HLS PIPELINE

    // This is the accumulator that will sum up the products.
    // It will be synthesized into a register.
    acc_t acc = 0;

    // This loop performs the multiply-accumulate (MAC) operation.
    MAC_Loop:
    for (int i = N_TAPS - 1; i >= 0; i--) {
        if (i == 0) {
            // In the first iteration, load the new input sample into the register.
            shift_reg[0] = input;
        } else {
            // For all other iterations, shift the data down the register chain.
            shift_reg[i] = shift_reg[i - 1];
        }
        // Multiply the stored sample by its corresponding coefficient and add to the accumulator.
        acc += shift_reg[i] * fir_coeffs[i];
    }

    // Assign the final accumulated value to the output.
    *output = acc;
}
