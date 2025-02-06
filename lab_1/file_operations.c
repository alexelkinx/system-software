#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_books_from_file(Book_t *library, int *book_count, const char *filename)
{
    FILE *file = fopen(filename, "r"); // Open the file in read mode ("r")

    if (file == NULL)
    {
        printf("File not found. Starting with an empty library.\n");
        return;
    }

    char line[100]; // Buffer for reading lines from the file, limit 100 chars per line

    // Read each line from the file until reaching the end of the file
    // fgets reads a line of text from the file
    while (fgets(line, sizeof(line), file))
    {
        if (*book_count >= N) // Ensure we do not exceed the library size
        {
            printf("Library capacity reached. Some books may not be loaded.\n");
            break; // Stop loading if library is full
        }

        Book_t book;          // Temporary `book` object to hold parsed book data
        char loan_status[10]; // Buffer to store the loan status string (array of chars) (e.g., "loaned" or "available")

        /*
        int sscanf(const char *str, const char *format, ...) -  “string scan formatted”
        • str: The input string from which data is to be extracted (the line string contains values separated by commas).
        • format: A format string "%hu,%49[^,],%49[^,],%9s" tells sscanf to extract the following:
            - %hu: An unsigned short integer (id)
            - %49[^,]: A string of up to 49 characters (title) until a comma is encountered
            - %49[^,]: Another string of up to 49 characters (author) until a comma is encountered
            - %9s: A string of up to 9 chars (status)
        • ...: Pointers to variables where the extracted values should be stored.
        sscanf returns the number of successful matches, so we can check if the correct number of values was extracted [4]
        */

        // Parse the line, expecting the format: id, title, author, loan status -> extract data using pointers and store in book.id...
        // & needed for book.id (primitive type (uint16_t)) to pass its memory address and modify its value directly
        if (sscanf(line, "%hu,%49[^,],%49[^,],%9s", &book.id, book.title, book.author, loan_status) == 4)
        {
            book.is_loaned = strcmp(loan_status, "loaned") == 0; // if is "loaned" -> set the `is_loaned` flag
            library[*book_count] = book;                         // Add the book to the library at the current index
            (*book_count)++;                                     // Increment book count
        }
        else
        {
            printf("Warning: Unable to parse line: %s\n", line); // If the line doesn't match the expected format
        }
    }

    fclose(file); // Close the file after reading
}

void save_books_to_file(Book_t *library, int book_count, const char *filename)
{
    FILE *file = fopen(filename, "w"); // Open the file in write mode ("w")

    // If the file cannot be opened for writing
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    // Iterate through all books in the library and write each book's data to the file
    for (int i = 0; i < book_count; i++)
    {
        /*
        fprintf (“file print formatted”) is used to write formatted data to a file
        int fprintf(FILE *stream, const char *format, ...);
        • stream: The file pointer to which the formatted data should be written
        • format: A format string defines the structure of the output ("int1,str2..\n"):
            - %hu: Writes an unsigned short integer to the file
            - %s: Writes a string to the file
        • ...: values that will be formatted according to the format string and written to the file
        */

        // Write book data in CSV format: id, title, author, loan status (either "loaned" or "available")
        fprintf(file, "%hu,%s,%s,%s\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].is_loaned ? "loaned" : "available");
    }

    fclose(file);
}