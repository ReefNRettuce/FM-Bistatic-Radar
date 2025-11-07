
/*
Least Mean Squares algorithm

Description: The least mean squares algorithm tries to minimize the error between a reference 
and echo signal using least squares. It suffers from explosions (occasionally) but its a good starting point. 

echo signal in the literature/online this is the noisy signal. Reference Signal is the signal that we're trying to minimize the sum of the square errors for. So the output of the filter which I'm going to rename filtered signal is the weights * the input signal. The error is the value of the desired signal minus the output. We want to lower the error as much as possible.
Inputs: input_signal (echo signal), reference signal (reference signal), step size (learning rate), out signal (filter output signal), error_signal (signal we want to minimize)

steps: 
output equals filter weights * input 
calculate error: e(n) = d(n) - y(n). the error equals the desired signal value minus the filter output
update the weights: w(n) = w(n-1) + 2*(step_size)*error*x(n)
the new weight value is equal to the old weight value plus two times the step size error and input signal value
write all these values to your new place 
*/



#include <cmath>
#include <math.h>
#include <cstdint>
#include <hls_stream.h>

typedef int signal_t;
typedef int data_t;
typedef int coeff_t;

void lms_filter(hls::stream<signal_t> input_signal, hls::stream<signal_t> reference_signal,
int step_size, hls::stream<signal_t> out_signal, hls::stream<signal_t> error_signal){
    // should this be void? 
    //okay so what are we doing 


    //declare variables 
    //I declare the varialbes here that only need to be declared once and not 50 times 
    //Add shift register complete pragma here HLS ARRAY PARTITION SHIFT REGISTER COMPLETE
    //each weight has to be updated and multipled by the error of the previous stuff 
    static data_t weights_shift_register[50] = {0}; //filter order is fifty
    static signal_t output_temp = 0;
    static data_t input_temp = 0;
    static data_t temp = 0;
    static signal_t error_temp = 0;
    
    //read the streams 
    //initiliaze the first value
Output_Loop:

    for(int n=0;n<50;n++){
            //pragma unroll full
            //this is my mulitply accumulate loop
            //calculate the output
            //for value one do this outside the loop
            temp = input_temp * weights_shift_register[n];
            output_temp = output_temp + temp;
        }
    output_temp = out_signal.write();

    //reset output_temp for next sample 
    output_temp = 0;

Error_Loop: 
    //not really loops but whatever
    signal_t desired_signal = reference_signal.read();

    for(int n=0;n<50;n++){

        //pragma unroll full
        error_signal = desired_signal - error_signal;
    }

Update_Loop: 

    weights_shift_register[0] = 0 + (( 2*error_signal*input_signal.read() ) << 7);

    for (int n=1;n<50;n++){
        //pragma unroll full
        weights_shift_register[n] = weights_shift_register[n-1] + (( 2*error_signal*input_signal.read() ) << 7);
    }

//brain done do later.
}

