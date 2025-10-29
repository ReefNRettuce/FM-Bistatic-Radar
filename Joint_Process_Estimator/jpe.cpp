/*this is a joint process estimator
//composed of two DSP structures.
//The Gradiant Adaptive Lattice
The Normalized Least Mean Squares (NLMS) transveral Delay Line (TDL)
*/
#include <cstdint>
#include <stdint.h>
#include <hls_stream.h>
#include <hls_task.h>

typedef int data_t;

void gal_stage(hls::stream<data_t> echo_signal, hls::stream<data_t> reference_signal);


void joint_process_estimator(hls::stream<data_t> echo_signal,hls::stream<data_t> reference_signal){
    int end = sizeof(reference_signal);
    
    //not sure how to declare the variables of the actual gal stage 
    //now we pass everything to the gradiant adaptive lattice    
    for(int i = 0;i<=end;i++){
        
    }



}
