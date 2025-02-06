#include "library.h"
#include "file_operations.h"
#include <stdio.h>
#include <stdlib.h> // For malloc and free
#include <string.h>

int main(int argc, char *argv[])
{
    // Check if the user provided the library filename in cmd
    if (argc < 2)
    {
        printf("Usage: %s <library_filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    char *command = (char *)malloc(10 * sizeof(char));      // Dynamically allocates memory for a string input of up to 10 characters
    Book_t *library = (Book_t *)malloc(N * sizeof(Book_t)); // Dynamically allocate memory for N books
    int book_count = 0;                                     // Current number of booksmake

    load_books_from_file(library, &book_count, filename);

    printf("Total books loaded: %d\n", book_count);

    // Check if memory allocation was successful
    if (command == NULL || library == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1; // Exit if malloc fails
    }

    while (1) // To use while (true), we need to include the <stdbool.h>
    {
        printf("\nEnter command (add, del, list, lall, lone, loan, return, exit): ");
        scanf("%9s", command); // Read a string of max 9 chars (1 char reserved for null terminator)

        // Switch-case to handle commands
        switch (command[0])
        {
        case 'a':
            if (strcmp(command, "add") == 0) // strcmp() returns 0 if the two strings are equal
            {
                add_book(library, &book_count);                    // Passing 'library' (by default holds the memory address of the array) and '&book_count' (address of book_count for modification).
                save_books_to_file(library, book_count, filename); // Save after adding
            }
            else
            {
                printf("Unknown command, please try again.\n"); // Unknown command that start with 'a'
            }
            break;
        case 'd':
            if (strcmp(command, "del") == 0)
            {
                delete_book(library, &book_count);                 // book_count is passed by value as it’s only being read
                save_books_to_file(library, book_count, filename); // Save after deletion
            }
            else
            {
                printf("Unknown command, please try again.\n");
            }
            break;
        case 'l':
            if (strcmp(command, "list") == 0)
            {
                list_available_books(library, book_count);
            }
            else if (strcmp(command, "lall") == 0)
            {
                list_all_books(library, book_count);
            }
            else if (strcmp(command, "lone") == 0)
            {
                uint16_t id;
                printf("Enter book ID: ");
                scanf("%hu", &id); // %h - a short int; with u - an unsigned short int.
                show_book_details(library, book_count, id);
            }
            else if (strcmp(command, "loan") == 0)
            {
                uint16_t id;
                printf("Enter book ID: ");
                scanf("%hu", &id);
                loan_book(library, book_count, id);
                save_books_to_file(library, book_count, filename); // Save after loaning
            }
            else
            {
                printf("Unknown command, please try again.\n");
            }
            break;
        case 'r':
            if (strcmp(command, "return") == 0)
            {
                uint16_t id;
                printf("Enter book ID: ");
                scanf("%hu", &id);
                return_book(library, book_count, id);
                save_books_to_file(library, book_count, filename); // Save after returning
            }
            else
            {
                printf("Unknown command, please try again.\n");
            }
            break;
        case 'e':
            if (strcmp(command, "exit") == 0)
            {
                printf("Exiting program...\n");
                save_books_to_file(library, book_count, filename);
                free(command); // Free allocated memory before exiting
                free(library);
                return 0; // Exit the program
            }
            else
            {
                printf("Unknown command, please try again.\n");
            }
            break;
        default:
            printf("Unknown command, please try again.\n");
            break;
        }
    }

    // These lines won't be reached because of the infinite loop
    free(command); // Free allocated memory before exiting
    free(library);
    return 0;
}