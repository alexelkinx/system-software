#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"
#include "error_codes.h"

// 'const char *filename' is a pointer to a constant string representing the
// filename to be read. The 'const' qualifier ensures the function does not
// modify the string, promoting safer code and preventing accidental changes.

// The size for 'char timestamps[MAX_SAMPLES][20]' is specified to inform the compiler
// how to correctly calculate the addresses of the elements in the second
// dimension. For single-dimensional arrays like 'float input_data[MAX_SAMPLES]',
// the size is not needed in the function parameter because C can work with just
// the pointer to the first element.
int read_csv(const char *filename, float *data, char timestamps[MAX_SAMPLES][20], int *num_samples)
{
    // FILE *file is a pointer to a FILE structure that represents an open file.
    // Using a pointer allows the program to manage the file's state (like the current
    // read/write position) without needing to know the details of the FILE structure.
    // It also enables dynamic memory management, as fopen allocates memory for the FILE
    // structure and returns a pointer to it, allowing multiple operations on the same
    // file while maintaining its state.
    FILE *file = fopen(filename, "r");
    if (file == NULL) // same as if (!file)
    {
        perror("Error opening file for reading"); // Use perror to display error message
        return FILE_NOT_FOUND;
    }

    char line[50]; // Buffer to hold each line of the CSV
    int i = 0;

    // Skip the header line
    // fgets function reads and discards the header/first line from the CSV file
    // fgets also moves the file pointer forward to the beginning of the next/second line
    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        return FILE_HAS_NO_CONTENT; // If the file is empty or has no valid lines
    }

    // Read the data line by line startin from the second one
    while (fgets(line, sizeof(line), file) != NULL && i < MAX_SAMPLES)
    {
        // Pointer to store the entire token (string) returned by strtok(), not just one char.

        // First call to strtok(line, ","):
        //  - The input string 'line' is "2024-10-13T07:00,15.5".
        //  - strtok() scans until the first comma and replaces it with a null terminator '\0'.
        //  - Now, 'line' becomes: "2024-10-13T07:00\015.5" (comma replaced by '\0').
        //  - Pointer 'token' points to the first token, which is "2024-10-13T07:00".
        char *token = strtok(line, ",");
        if (token != NULL) // Ensures that the first token was successfully found and is not NULL
        {
            // Copy the token (timestamp) to the timestamps array
            // If the source string is shorter than the specified number, strncpy will fill the
            // remaining space in the destination with null characters. However, if the source
            // string is equal to or longer than the specified number, strncpy will not
            // automatically add a null terminator and that's when we need next step.
            strncpy(timestamps[i], token, sizeof(timestamps[i]));

            // Ensure null termination by setting the last character of the array to '\0'
            // This guarantees the string is properly terminated
            timestamps[i][sizeof(timestamps[i]) - 1] = '\0';
        }

        // Second call to strtok(NULL, ","):
        //  - strtok(NULL, ",") resumes scanning the same string after the first null terminator.
        //  - It starts scanning after "2024-10-13T07:00\0", where the second token starts.
        //  - Pointer 'token' now points to the second token, which is "15.5".
        token = strtok(NULL, ",");
        if (token != NULL)
        {
            // Convert pointer to the string 'token' to a float and store the temperature.
            // The strtof function converts a C string (character array) to a float,
            // scanning for a valid floating-point number representation while skipping
            // leading whitespace. It returns the converted float value.
            // The second parameter, set to NULL, indicates where to stop parsing;
            // in this case, we don't need to know where the conversion stopped
            // since we're only interested in the float value. If the string is
            // not a valid number, it returns 0.0.
            data[i] = strtof(token, NULL);
            i++;
        }
    }
    // By passing the address of 'num_samples' (&), we can modify its value directly in the
    // function. This allows us to update the actual data via the pointer (*num_samples)
    // without needing to return anything.
    *num_samples = i; // Store the actual number of samples read
    fclose(file);
    return (i > 0) ? SUCCESS : FILE_HAS_NO_CONTENT; // Check if any data was read
}

int write_csv(const char *filename, float *data, char timestamps[MAX_SAMPLES][20], int num_samples, FilterType filter_type)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        return FILE_WRITE_ERROR;
    }

    const char *filter_name;
    if (filter_type == MOVING_AVERAGE)
    {
        filter_name = "Moving Average";
    }
    else if (filter_type == LOW_PASS)
    {
        filter_name = "Low Pass";
    }
    else
    {
        filter_name = "Unknown";
    }

    // Write the header line including filter type
    fprintf(file, "FilterType,DateTime,Temperature (°C)\n");

    for (int i = 0; i < num_samples; i++)
    {
        fprintf(file, "%s,%s,%.2f\n", filter_name, timestamps[i], data[i]); // Write timestamp and temperature
    }

    fclose(file);
    return SUCCESS;
}