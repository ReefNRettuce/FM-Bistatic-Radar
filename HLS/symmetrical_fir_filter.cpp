#define taps 24
#include "ap_int.h"
//taps is the number of taps made by matlab. 
//ap_int.h is apparently and arbitrary integer type 

typedef int coeff_t;
typedef int data_t;
typedef int acc_t;
//these are all typedefs whats is a type define again? 

void fir_optimized(data_t *output, data_t input) {
    coeff_t coefficients[taps] ={25,48,59,24,-84, -260,-453,-569,-514,
  -246,173,576,742,510,-114,-904,-1456,-1341,-295,1619,3984,6141,7425  
    };
    
    static data_t shift_reg[taps] = {0};
    acc_t acc = 0;
    
    // --- SHIFTING LOGIC GOES HERE FIRST ---
    // (A simple loop to shift all elements of shift_reg and insert 'input' at index 0)
    Shift_Loop:
    for (int i = taps - 1; i > 0; i--) {
        shift_reg[i] = shift_reg[i-1];
    }
    shift_reg[0] = input;
    // --- END SHIFTING LOGIC ---

    // Loop through the first half of the filter
    Folded_MAC_Loop:
    for (int i = 0; i < (taps); i++) {
        // 1. Perform the pre-addition for the symmetrical pair
        // The formula for the symmetrical index is (N_TAPS - 1) - i
        data_t pre_add_result = shift_reg[i] + shift_reg[(taps - 1) - i];

        // 2. Multiply by the single coefficient and accumulate
        // Note: The fir_coeffs array would only need to store the first half
        acc += pre_add_result * coefficients[i];
    }

    // 3. After the loop, add the product for the unique center tap
    int center_tap_index = taps / 2;
    acc += shift_reg[center_tap_index] * coefficients[center_tap_index];

    *output = acc;
}