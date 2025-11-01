#include <cmath>
#include <math.h>
#include <cstdint>
#include <hls_stream.h>

//something needs to change here so that I can passe the array
typedef int signal_t;
typedef int data_t;
typedef int coeff_t;

//I will mess with the integer size later

signal_t lms_filter(hls::stream<signal_t> &input_signal, hls::stream<signal_t> &reference_signal,
double step_size, hls::stream<signal_t> &out_signal, hls::stream<signal_t> &error_signal);

int main() {
    // --- Signal Parameters ---
    const int NUM_SAMPLES = 200000;
    const double SAMPLING_RATE = 200000; // Samples per second (like a CD)
    const double FREQUENCY = 100.0;  // We want a 100 Hz wave
    const double AMPLITUDE = 1; // Max value of the wave

    // Array to store our generated signal
    double baseband_signal[NUM_SAMPLES];

    // --- The Generation Loop ---
    for (int i = 0; i < NUM_SAMPLES; i++) {
        double t = (double)i / SAMPLING_RATE;
        
        double angle_rad = 2.0 * M_PI * FREQUENCY * t;
        baseband_signal[i] = AMPLITUDE * cos(angle_rad);
    }
    

    //okay now we've qunatized the baseband 
    //now we're going to produce to other signals one thats the reference and echo signal

    double echo_baseband[NUM_SAMPLES] = {0};
    double reference_baseband[NUM_SAMPLES] = {0};
    
    //this is 
    double reference_attenuation_factor = 1;
    double attenuation_db = -3;
    double echo_attenuation_factor = pow(10, attenuation_db/20);

    //now we're going to corrup the echo signal with random white noise
    double k = 0; //white noise is k and it is a random number

    for(int i =0; i<NUM_SAMPLES; i++){
        k = ( rand() % 100 + 0)/100.00;

        echo_baseband[i]= baseband_signal[i] * echo_attenuation_factor + k;
        reference_baseband[i] = baseband_signal[i] * reference_attenuation_factor;
    }

    hls::stream<signal_t> echo_signal;
    hls::stream<signal_t> reference_signal;
    hls::stream<signal_t> error_signal;
    hls::stream<signal_t> output_signal;
    
    //write to the streams
    //Do I use HLS Pragma Dataflow here?
    for(int i=0;i<NUM_SAMPLES;i++){
        //we quantize and cast to int in this step
        int temp1 = (signal_t)(reference_baseband[i] * 32768);
        //writing the stream here 
        echo_signal.write(temp1);

        int temp2 = (signal_t)(echo_baseband[i] * 32768);
        reference_signal.write(temp2);
    }

    //the producer loop has produced the data 
    //now we need to eat the data. 
    for(int i=0;i<NUM_SAMPLES;i++){
        //we pass the echo, reference, step size, and error signal in
        lms_filter(echo_signal, reference_signal, 0.01, output_signal, error_signal);
    }

    
}