#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "fir_filter.h"

// Define the data types to match the HLS design
typedef int data_t;

// Prototype for the function we are testing (the "Design Under Test" or DUT)
void fir_filter(data_t *output, data_t input);

// This is the main function for our testbench.
// It is NOT synthesizable and runs only on the host computer for verification.
int main() {
    // --- Testbench Setup ---
    const int NUM_SAMPLES = 256;
    std::vector<data_t> input_signal(NUM_SAMPLES);
    std::vector<data_t> output_signal;
    data_t single_output;

    // Create a test signal: a combination of a low-frequency sine wave (should pass)
    // and a high-frequency sine wave (should be blocked by the filter).
    // Fs = 10000 Hz, f1 = 500 Hz, f2 = 2500 Hz
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        double low_freq_component = sin(2 * M_PI * 500 * i / 10000);
        double high_freq_component = sin(2 * M_PI * 2500 * i / 10000);
        // Scale and convert to our integer data type
        input_signal[i] = static_cast<data_t>((low_freq_component + high_freq_component) * 1000);
    }

    // --- Run the Simulation ---
    // Call the HLS filter function for each sample, just like the hardware would.
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        fir_filter(&single_output, input_signal[i]);
        output_signal.push_back(single_output);
    }

    // --- Verify the Output ---
    // Save the input and output signals to a text file for analysis.
    // You can then plot these in MATLAB or any other tool to see the filter's response.
    std::ofstream outFile("results.txt");
    if (outFile.is_open()) {
        outFile << "Input,Output\n";
        for (int i = 0; i < NUM_SAMPLES; ++i) {
            outFile << input_signal[i] << "," << output_signal[i] << "\n";
        }
        outFile.close();
        std::cout << "Dinosaur Simulation finished. Results saved to results.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
        return 1; // Error
    }

    // The testbench should return 0 if the test passes.
    // (Here, we assume it passes if it runs without error).
    return 0;
}
