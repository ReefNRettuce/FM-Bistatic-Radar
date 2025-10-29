/*
Joint Process estimator (JPE)

Description: 
The JPE is essentially trying to minimize the error between whats expected from the reference signal and the actual echo signal received. There are two main sources of error present in our FM radio signals. First is the actual FM radio broadcast. It is essentially an interferer to the echo signal. And second is the noise and attenuation picked up along the way from the radio tower to the track and back. This is the context I needed to understand to understand WHY we need a JPE in the first place. 
The joint process estimator is good for filtering colored noise. The input into the 
JPE is the echo signal. The echo signal and reference signal 'similarity' (autocorrelation matrix) is high. Therefore to use the NLMS TDL we need to first remove the colored noise or 
decorrelate the two signals. Secondly the echo signal and the reference signal are basically copies of each other except that one is much more highly attenuated. (There should also be a huge time delay or frequency shift like the doppler effect is essentially what we're measuring)
The joint process estimator first uses a gradiant adaptive lattice (GAL) to de-correlate the two FM radio broadcast signals. 
Then the NLMS TDL takes the backward propagation errors from the GAL and uses those as its inputs. This then allows the filter to minimize the mean square error. 

Input Parameters:
echo signal is the signal that has bounced off of the track. 
reference signal is the signal from the FM radio broadcast tower.  

Output Parameters:
error_signal

Relevant Equations
*/

#include "math.h"
#include <cmath>
#include <cstdint>

//change these to something that works
typedef int signal_t;
typedef int data_t;
typedef int coeff_t;

void gradiant_adaptive_lattice(signal_t echo_signal, signal_t error_signal, coeff_t f_err,
coeff_t b_err, coeff_t k_coeff)
{
    //now I'm going to declare the internal state variables 
    //(FOR LATER should I change the reflection coefficient so that I don't have to read and write aka save on data transfers)    

   //b_err_prev, k_coeff_prev are the previous variables and are stored
    static coeff_t b_err_prev = 0;
    static coeff_t b_err_new = 0;
    static coeff_t k_coeff_prev = 0;
    static coeff_t k_coeff_new = 0;
    static coeff_t f_err_new = 0;

    //next we're going to going into a read state
    //the update equations are changed here 

    //first the previous forward propagation error is read 
    //the current f_err is set equal to the previous error
    f_err_new = f_err - conj(k_coeff_prev) * b_err_prev;
    //now I need to output this f_err_new how do I do that? 

    //next the previous backward propagation error is read aka calculated 
    b_err_new = b_err_prev - f_err*conj(k_coeff_prev);
    b_err_out = b_err_prev;

    //next the new k coefficient is calculated 
    k_coeff_new = k_coeff_prev - 2*f_err_new*b_err_prev;
}



void joint_process_estimator(signal_t echo_signal, signal_t reference_signal, signal_t error_signal, int NUM_SAMPLES){
    //each stage of the gradiant adaptive lattice has three state variables; reflection coefficients, forward propagation error, backwards propagation error
    //these are all static signals because they are only declared on the first stage

    static signal_t reflection_coefficient[50] = {0};
    static signal_t f_prop_err[50] = {0};
    static signal_t b_prop_err[50] = {0};


    //call the gradiant adaptive lattice function
    //for look is the entire number of samples
    for(int i=0; i<NUM_SAMPLES;i++){
        for(int j=0; j<50;j++){
            gradiant_adaptive_lattice(echo_signal[i], error_signal[i], f_prop_err[i], b_prop_err[i], reflection_coefficient[i]);
        //how do I output the coefficients as an output? or is it 
        //if I call the functions as f_prop_err[i-1] what do I do when i = 0? should I just push that out of the for loop? like before the for loop just call the GAL function
        }
        
    }
}



