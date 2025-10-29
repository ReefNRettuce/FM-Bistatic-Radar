
#include <cmath>
#include <math.h>
#include <cstdint>

//something needs to change here so that I can passe the array
typedef int signal_t;
typedef int data_t;
typedef int coeff_t;

//I will mess with the integer size later

void joint_process_estimator(signal_t echo_signal, signal_t reference_signal, signal_t error_signal, const int NUM_SAMPLES);

int main() {
    // --- Signal Parameters ---
    const int NUM_SAMPLES = 200000;
    const double SAMPLING_RATE = 200000; // Samples per second (like a CD)
    const double FREQUENCY = 100.0;  // We want a 10 Hz wave
    const double AMPLITUDE = 10000.0; // Max value of the wave

    // Array to store our generated signal
    double baseband_signal[NUM_SAMPLES];

    // --- The Generation Loop ---
    for (int i = 0; i < NUM_SAMPLES; i++) {
        double t = (double)i / SAMPLING_RATE;
        
        double angle_rad = 2.0 * M_PI * FREQUENCY * t;
        baseband_signal[i] = AMPLITUDE * cos(angle_rad);
    }
    
    //now we need to quantize the signal 
    signal_t quantized_baseband_signal[NUM_SAMPLES];
    for(int i = 0; i<NUM_SAMPLES; i++){
        quantized_baseband_signal[i] = signal_t (baseband_signal[i]*32767.0);
    }

    //okay now we've qunatized the baseband 
    //now we're going to produce to other signals one thats the reference and echo signal

    //we're just going to do this easy and use an attenuation factor of 7.7*10^-11 for the echo (-71 dbm)
    //we're just going to do this easy and use an attenuation factor of 1000 for the reference signal (-30 dB) the signal is going from 10,000 watts to 10 watts. 
    signal_t temp_signal_1[NUM_SAMPLES] = {0};
    signal_t temp_signal_2[NUM_SAMPLES] = {0};
    
    double reference_attenuation_factor = pow(10, -30/20);
    double echo_attenuation_factor = pow(10,-40.0/20);

    for(int i =0; i<NUM_SAMPLES; i++){
        temp_signal_1[i]= quantized_baseband_signal[i] * echo_attenuation_factor;
        temp_signal_2[i] = quantized_baseband_signal[i] * reference_attenuation_factor;
    }

    signal_t echo_signal[NUM_SAMPLES] = {0};
    signal_t reference_signal[NUM_SAMPLES] = {0};
    signal_t error_signal[NUM_SAMPLES] = {0};
    //before this I need to add some sort of doppler so that we can actually measure something



    for(int i = 0; i<NUM_SAMPLES; i++){
        echo_signal[i] = (int)(temp_signal_1[i]);
        reference_signal[i] = (int)(temp_signal_2[i]);
    }

    //now we're finally going to do the stuff its what we've all been waiting for. 
    //outer loop is to go through all the samples after they're attenuated. 
    //removed the outer loops so that I can corretly simulate the sampling structure
    joint_process_estimator(echo_signal, reference_signal, error_signal);
    //(need to change I need to pass an entire array through this)   
}