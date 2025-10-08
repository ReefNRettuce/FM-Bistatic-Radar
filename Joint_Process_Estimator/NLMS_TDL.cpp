/*
The NLMS based TDL recevies the backwards_propagation_error as the input signals and then updates its coefficients each time for every sample. 
I may just make this one big function to test out the logic. 
input variables: 
backwards error propogation (b_err_op)
sample (sample) the first sample in the filter is actually the reference signal 
outputs an error
*/
#include <cstdint>
#include <stdint.h>
#include <hls_stream.h>
#include <hls_task.h>
#define number_of_samples 4096
#define number_of_taps 50

typedef int8_t coeff_t, data_t, reg_t;

void nlms_tdl(hls::stream<int8_t> b_err_op, hls::stream<int8_t> reference_signal, hls::stream<int8_t> error_signal){
    //the nlms functions very simliarly to a traditional FIR Filter. 
    //first we don't have a traditional set of coefficients like an FIR filter 
    
    
    // this is statis because each of the coefficients are not zero forever just when they initiliaze. 
    //I used int8_t because its pretty small and I want my filter to be smaller I can expand later once I see resource usage.
    static coeff_t a_coefficients[number_of_taps] = {0};
     
    //The digital filter is made of shift registers, and a multiply accumulate loop. 
    // In an adaptive filter the shift register and coefficients change and are updated every clock cycle
    static reg_t shift_register[number_of_taps] = {0};
    int8_t accumulate = 0; 

    //Now I'm going to use the array partition pragma. Since I need to change this every clock cycle I need it to be in a partitioned
    //shift register 
    #pragma HLS ARRAY_PARTITION variable= shift_register complete
    
    /*
    now we're actually going to do the shift loop.
    for readability I'm going to declare a variable named input. 
    Input is just the backwards propogation error that is output from the GAL filter
    the shift loop starts at the last value in the array and moves all the other values stored in the shift register to the next 
    shift register. We did it backwards to avoid using an IF statement inside the for loop. 
    also we unroll this entire loop so that it happens all at once. 
    */
    SHIFT_LOOP: 
    //I have no idea if this is correct. I hope it is. 
    for(int i = number_of_taps - 1; i>0; i-- ){
        #pragma HLS UNROLL
        shift_register[i]= shift_register[i-1];
    }
    shift_register[0]= b_err_op;

    MAC_LOOP:
    /*
    Now we're going to do the multiply accumulate loop. 
    This one is simpler but less efficient than a folded loop
    */
    for(int j= 0; j<= number_of_taps;j++){
        #pragma HLS PIPELINE
        accumulate += a_coefficients[j] * shift_register[j]; 
    }

    Update_Equation: 
    /*
    Now we're going to update all of the filter coefficients
    Man this is gonna be expensive in terms of resources. 
    This loop goes through all of the filter coefficients and updates them. This is what makes it adaptive
    We're going to have a pre-addition step and then a multiplaction step. 
    Note: TO DO I may want to play with the actual size of the integers to like 7 or 8 or something. 
    we start at i=1 to make sure we don't have an out of bounds array
    */
    int8_t denominator = 0;
    int8_t numerator = 0;
    int8_t temp = 0;
    const float rate = 0.01;
    #pragma HLS ARRAY_RESHAPE variable= a_coefficients dim=1 type=complete //I know I need to turn the array of the samples into a column vector TO DO
    for(int i = 1; i<= number_of_taps;i++){
        //step 1 calculate the pre steps (going to assume the column to row vector thing just works for now.)
        #pragma HLS PIPELINE //not sure if I should pipeline or unroll this
        denominator = b_err_op[i] * b_err_op[i];
        numerator = rate * error_signal[i] * b_err_op[i];
        temp = numerator/denominator;
        a_coefficients[i] = a_coefficients[i-1] + temp;
    }

}
