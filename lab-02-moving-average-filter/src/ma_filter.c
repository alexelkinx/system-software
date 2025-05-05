#include <stdio.h>
#include "filter.h"
#include "error_codes.h"

/*
 * Function: moving_average_filter
 * -----------------------------
 * Applies a moving average filter to the input array.
 *
 * Parameters:
 * - float *input: Pointer to the input array of values.
 * - float *output: Pointer to the output array to store moving averages.
 * - int num_samples: The total number of samples in the input array.
 * - int taps: The size of the moving average window (number of samples to average).
 *
 * Returns:
 * - SUCCESS on successful completion.
 * - NULL_POINTER_ERROR if input or output is NULL.
 * - INVALID_NUM_SAMPLES_ERROR if num_samples is less than or equal to 0.
 * - INVALID_TAPS_ERROR if taps is less than or equal to 0.
 * - TAPS_EXCEEDS_SAMPLES_ERROR if taps exceeds num_samples.
 *
 * Rule for Calculating the Moving Average:
 *
 * The moving average is calculated by taking the average of a specific number of consecutive
 * samples, called the "window size" or "taps".
 *
 * For each position 'i' in the input array:
 * 1. Start at the current sample 'i'.
 * 2. Sum the current sample and the previous 'taps - 1' samples.
 *    - If there are fewer than 'taps' samples (for the first few samples), sum only the available ones.
 * 3. Divide the sum by the number of valid samples to get the moving average for that position.
 * 4. Store the result in the output array, with the moving averages for each position in the input array.
 *
 * Example:
 *
 * Input array: [10, 20, 30, 40, 50]
 * Taps = 3 (window size):
 *
 * - At i = 0: The window contains [10]. Average = 10 / 1 = 10.
 * - At i = 1: The window contains [10, 20]. Average = (10 + 20) / 2 = 15.
 * - At i = 2: The window contains [10, 20, 30]. Average = (10 + 20 + 30) / 3 = 20.
 * - At i = 3: The window contains [20, 30, 40]. Average = (20 + 30 + 40) / 3 = 30.
 * - At i = 4: The window contains [30, 40, 50]. Average = (30 + 40 + 50) / 3 = 40.
 *
 * Output array (Moving Averages): [10, 15, 20, 30, 40]
 *
 * Explanation:
 * The moving average "slides" over the input array, recalculating the average at each step by including
 * the next sample and discarding the oldest one (once enough samples are available to fill the window).
 */

int moving_average_filter(float *input, float *output, int num_samples, int taps)
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

    if (taps <= 0) // Check if taps is valid
    {
        fprintf(stderr, "Error: Number of taps must be greater than 0.\n");
        return INVALID_TAPS_ERROR;
    }

    if (taps > num_samples) // Ensure taps does not exceed the number of samples
    {
        fprintf(stderr, "Error: Number of taps (%d) cannot exceed number of samples (%d).\n", taps, num_samples);
        return TAPS_EXCEEDS_SAMPLES_ERROR;
    }

    for (int i = 0; i < num_samples; i++) // Loop through each sample in the input array
    {
        // Sum of the values in the current window
        // Reset to 0 at the start of each iteration/window
        float sum = 0;

        // Amount of samples in the current window
        // Also reset at the start of each iteration
        int count = 0;

        // Calculate moving average for the current window
        for (int j = 0; j < taps; j++)
        {
            if (i - j >= 0) // Check that we don't go out of bounds (negative indices)
            {
                sum += input[i - j]; // Add the value of the current sample (or previous samples) to the sum
                count++;             // Count how many valid samples have been summed for the current window
            }
        }

        // Store the average in the output array
        // Average based on how many samples were counted
        output[i] = sum / count;
    }

    return SUCCESS;
}