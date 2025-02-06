/*
Header file that contain the Book_t struct definition and declarations for functions related to managing the library.

The `#ifndef`, `#define`, and `#endif` directives are known as include guards. It ensures that this header file (library.h) is only included once during the compilation process, even if it’s included multiple times in different files.
*/

#ifndef LIBRARY_H // Start of the include guard. Checks if LIBRARY_H is not defined.
#define LIBRARY_H // Define the LIBRARY_H macro, to mark this file as included and prevent further inclusion.

#include <stdint.h>
#include <stdbool.h>

#define N 15 // Define the maximum number of books

// Define the Book_t struct
typedef struct
{
    uint16_t id;    // ID of the book (unsigned int, 16 bits)
    char title[50]; // Title of the book (max 50 chars)
    char author[50];
    bool is_loaned; // Boolean to track if the book is loaned
} Book_t;           // Typedef struct allows using "Book_t" as the type instead of "struct Book"

// Function declarations for library management
void add_book(Book_t *library, int *book_count);
void delete_book(Book_t *library, int *book_count);
void list_available_books(Book_t *library, int book_count);
void list_all_books(Book_t *library, int book_count);
void show_book_details(Book_t *library, int book_count, uint16_t id);
void loan_book(Book_t *library, int book_count, uint16_t id);
void return_book(Book_t *library, int book_count, uint16_t id);

#endif // End of the include guard LIBRARY_H. Prevents multiple inclusion by closing the conditional.