#include <stdio.h>
#include "filter.h"
#include "error_codes.h"

// Define the filter taps array
static float filter_taps[LOW_FILTER_TAP_NUM] = {
    -0.003265, -0.005486, -0.005708, -0.001495, 0.009986,
    0.028543, 0.052008, 0.074376, 0.087962, 0.086341,
    0.066852, 0.032775, -0.010089, -0.050012, -0.075348,
    -0.076921, -0.051134, -0.003789, 0.053634, 0.110723,
    0.153328, 0.170111, 0.153328, 0.110723, 0.053634,
    -0.003789, -0.051134, -0.076921, -0.075348, -0.050012,
    -0.010089};

// Low-Pass Filter implementation using moving_average_filter
int low_pass_filter(float *input, float *output, int num_samples, int moving_average_taps)
{
    if (input == NULL || output == NULL) // Check for null pointers
    {
        fprintf(stderr, "Error: Input or output array is NULL.\n");
        return NULL_POINTER_ERROR;
    }

    if (num_samples <= 0) // Check if the number of samples is valid
    {
        fprintf(stderr, "Error: Number of samples must be greater than 0.\n");
        return INVALID_NUM_SAMPLES_ERROR;
    }

    if (moving_average_taps <= 0 || moving_average_taps > num_samples)
    {
        fprintf(stderr, "Error: Invalid moving average taps.\n");
        return INVALID_TAPS_ERROR;
    }

    // Step 1: Apply the moving average filter to smooth the input data
    float temp[num_samples];
    int result = moving_average_filter(input, temp, num_samples, moving_average_taps);
    if (result != SUCCESS) // If moving average filter fails, return error
    {
        return result;
    }

    // Step 2: Apply low-pass FIR filter to the moving average results
    for (int i = 0; i < num_samples; i++)
    {
        output[i] = 0.0f; // Initialize the output value for this sample

        // FIR filter convolution on the moving average result
        for (int j = 0; j < LOW_FILTER_TAP_NUM; j++)
        {
            if (i - j >= 0)
            {
                // Multiply each filter tap by the corresponding sample in the moving average data
                output[i] += filter_taps[j] * temp[i - j];
            }
        }
    }

    return SUCCESS;
}