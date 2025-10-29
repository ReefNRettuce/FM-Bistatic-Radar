#include <cstdint> // or <stdint.h>
#include <hls_stream.h>


void gal_stage(){
    /*
    Description: a single stage GAL for use in an FM Bistatic Radar
    Inputs/Outputs
    forward propagation error input (f_err_inp) is the previous input from the previous stage
    backward propagation error input (b_err_input) is the previous backwards propogation error.
    forward propagation error output (f_err_op), and backward propagation error output (b_err_op) are the outputs. They're passed by reference. 
    */


// Internal Variables
    //only zero for the first iteration, holds reflection coefficient
    static int8_t k_coeff_prev = 0; 
    
    //only zero for the first iteration, holds backward propagation error in a delay 
    static int8_t b_err_prev = 0; 
    
    //step size for the adaptive filter
    const float u = 0.01; 

//READ STATE: we read the variables we need into a temporary set of place holders. 
    int8_t k_coeff = k_coeff_prev;
    int8_t b_err = b_err_prev;

//CALCULATE STATE: we calculate k_coeff_new, f_err_op, and b_err_op
    f_err_op = f_err_inp - conj(k_coeff_prev) * b_err;
    b_err_op = b_err + f_err_inp * k_coeff;
    int8_t k_coeff_new = k_coeff - (2 * u * b_err * f_err_inp);
    
    
//WRITE STATE: know write to the variable for the next stage
    b_err_prev = b_err_op;
    k_coeff_prev = k_coeff_new;

}