#include <stdio.h>
#include "filter.h"
#include "error_codes.h"

int apply_filter(float *input, float *output, int num_samples, FilterType filter_type)
{
    switch (filter_type)
    {
    case MOVING_AVERAGE:
        return moving_average_filter(input, output, num_samples, TAPS);
    case LOW_PASS:
        return low_pass_filter(input, output, num_samples, TAPS);
    default:
        return UNKNOWN_FILTER_TYPE;
    }
}