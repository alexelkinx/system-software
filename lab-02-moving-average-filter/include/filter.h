#ifndef FILTER_H
#define FILTER_H

#define MAX_SAMPLES 9000      // Maximum number of input samples
#define TAPS 63               // Number of taps for the moving average filter
#define LOW_FILTER_TAP_NUM 31 // Number of filter taps for a low-pass FIR filter

// Enumeration for different filter types
typedef enum
{
    MOVING_AVERAGE,
    LOW_PASS,
} FilterType;

int apply_filter(float *input, float *output, int num_samples, FilterType filter_type);
int moving_average_filter(float *input, float *output, int num_samples, int taps);
int low_pass_filter(float *input, float *output, int num_samples, int moving_average_taps);

#endif