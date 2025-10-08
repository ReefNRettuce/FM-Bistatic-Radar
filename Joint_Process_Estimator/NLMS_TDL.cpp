/*
The NLMS based TDL recevies the backwards_propagation_error as the input signals and then updates its coefficients each time for every sample. 

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

void nlms_tdl(hls::stream<int8_t> &b_err_op, hls::stream<int8_t> &reference_signal){
    //the nlms functions very simliarly to a traditional FIR Filter. 
    
}
