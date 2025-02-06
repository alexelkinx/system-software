#include <stdio.h>
#include <string.h>
#include "filter.h"
#include "error_codes.h"
#include "io.h"

// 'argc' is the argument count, indicating the number of command-line arguments.

// 'argv' is an array of strings (character pointers) representing the command-line arguments.
// Each element of this array points to a string representing an individual command-line argument.
// argv[0] is the program name, argv[1] is the first argument, and so on.
int main(int argc, char *argv[])
{
    // Default input and output file
    // Declaring the variable as a pointer to avoid copying the string, which saves
    // memory and allows efficient access to the string's location in memory.
    // Initialized since 'const' prevents changing the value later.
    const char *input_filename = "../data/temperature_data.csv";
    const char *output_filename = "../data/filtered_data.csv";

    FilterType filter_type = MOVING_AVERAGE; // Default filter type

    // If an input file was provided use it instead of the default
    if (argc >= 2)
    {
        input_filename = argv[1]; // Input file from command-line arguments
    }

    // If an output file was provided use it instead of the default
    if (argc >= 3)
    {
        output_filename = argv[2]; // Output file from command-line arguments
    }

    // Check the first argument (argv[1]) for filter type
    if (argc >= 4) // Ensure we have at least 4 arguments to check
    {
        if (strcmp(argv[3], "-low") == 0)
        {
            filter_type = LOW_PASS; // Set to Low Pass filter
        }
        else if (strcmp(argv[3], "-ma") == 0)
        {
            filter_type = MOVING_AVERAGE; // Set to Moving Average filter
        }
        else
        {
            fprintf(stderr, "Invalid filter type argument. Use -ma for Moving Average or -low for Low Pass.\n");
            return INVALID_ARGUMENT;
        }
    }

    // float instead of double for efficiency, as high precision isn't required for temperature readings
    float input_data[MAX_SAMPLES];
    float filtered_data[MAX_SAMPLES];

    // 2D array used to store date-time strings efficiently in memory, each up to 19 characters + null terminator
    char timestamps[MAX_SAMPLES][20];
    int num_samples = 0;

    // Read input data from the CSV file
    // &num_samples passes by reference the address of num_samples, allowing the
    // function to modify the value of num_samples in the main function using pionters
    ErrorCode read_result = read_csv(input_filename, input_data, timestamps, &num_samples);
    if (read_result != SUCCESS)
    {
        fprintf(stderr, "Error reading from file: %s (Error code: %d)\n", input_filename, read_result);
        return read_result; // Exit with error code
    }

    // Apply the selected filter (moving average in this case)
    ErrorCode filter_result = apply_filter(input_data, filtered_data, num_samples, filter_type);
    if (filter_result != SUCCESS)
    {
        fprintf(stderr, "Error applying filter (Error code: %d)\n", filter_result);
        return filter_result;
    }

    // Write the filtered data to the output CSV file
    ErrorCode write_result = write_csv(output_filename, filtered_data, timestamps, num_samples, filter_type);
    if (write_result != SUCCESS)
    {
        fprintf(stderr, "Error writing to file: %s (Error code: %d)\n", output_filename, write_result);
        return write_result;
    }

    printf("Filtering completed. Results saved to %s\n", output_filename);

    return SUCCESS;
}