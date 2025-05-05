#include "library.h"
#include <stdio.h>
#include <string.h>

// Book_t *library is a pointer to access the actual array of books, not a copy.
void add_book(Book_t *library, int *book_count) // pointer(*) needed to modify the count
{
    if (*book_count >= N)
    {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    // Temporary variables
    uint16_t new_id = 1;
    bool id_found = false;

    // Find the minimum unused ID
    while (id_found == false)
    {
        id_found = true; // Assume the ID is available
        for (int i = 0; i < *book_count; i++)
        {
            if (library[i].id == new_id) // Check if the ID is already in use
            {
                id_found = false; // ID is in use, check next ID
                new_id++;
                break; // Exit the for loop and check the next ID
            }
        }
    }

    // Temporary variable for book title and author
    char new_title[50];
    char new_author[50];

    // Read book title
    printf("Enter book title: ");
    scanf(" %[^\n]", new_title); // Reads a full line of input (including spaces) until a newline is encountered and stores it in new_title

    // Read author name
    printf("Enter author name: ");
    scanf(" %[^\n]", new_author); // Read until newline for author

    // Add the new book
    library[*book_count].id = new_id;                     // Assign ID directly to the array
    strncpy(library[*book_count].title, new_title, 50);   // Assign title
    strncpy(library[*book_count].author, new_author, 50); // Assign author
    library[*book_count].is_loaned = false;               // Mark as not loaned

    (*book_count)++; // Increment the book count; dereference needed to modify original value
    printf("Book added successfully with ID %hu!\n", new_id);
}

void delete_book(Book_t *library, int *book_count)
{
    if (*book_count == 0) // Check if the library is empty
    {
        printf("No books available to delete.\n");
        return;
    }

    uint16_t id_to_delete;
    printf("Enter book ID to delete (positive integer): ");
    if (scanf("%hu", &id_to_delete) != 1 || id_to_delete <= 0)
    { // Check if input is valid
        printf("Invalid ID. Please enter a positive integer.\n");
        while (getchar() != '\n')
            ;   // Clear input buffer
        return; // Exit the function
    }

    // Search for the book by ID
    for (int i = 0; i < *book_count; i++)
    {
        if (library[i].id == id_to_delete)
        {
            // Shift subsequent books to fill the gap
            for (int j = i; j < *book_count - 1; j++)
            {
                library[j] = library[j + 1]; // Move books one position up
            }

            (*book_count)--; // Decrement the book count
            printf("Book with ID %hu deleted successfully.\n", id_to_delete);
            return; // Exit the function
        }
    }

    // The book wasn't found
    printf("Book with ID %hu not found.\n", id_to_delete);
}

void list_available_books(Book_t *library, int book_count) // Does not need to modify count, so no pointer(*) needed
{
    printf("Available Books:\n");
    printf("%-5s %-30s %-25s\n", "ID", "Title", "Author"); // Print header
    // Print separator
    for (int i = 0; i < 60; i++)
    {
        printf("-"); // Print dashes
    }
    printf("\n");

    bool found = false; // Flag to check if any available books are found
    // Iterate through the library and list available books
    for (int i = 0; i < book_count; i++)
    {
        if (!library[i].is_loaned) // Check if the book is not loaned out
        {
            printf("%-5hu %-30s %-25s\n", library[i].id, library[i].title, library[i].author);
            found = true; // Mark that we found at least one available book
        }
    }

    if (!found) // If no available books were found
    {
        printf("No available books in the library.\n");
    }
}

void list_all_books(Book_t *library, int book_count)
{
    if (book_count == 0) // Check if the library is empty
    {
        printf("No books in the library.\n");
        return;
    }

    printf("Books in the Library:\n");
    printf("%-5s %-30s %-25s %-10s\n", "ID", "Title", "Author", "Loaned"); // Header
    // Print separator
    for (int i = 0; i < 70; i++)
    {
        printf("-"); // Print 70 dashes
    }
    printf("\n");

    for (int i = 0; i < book_count; i++)
    {
        printf("%-5hu %-30s %-25s %-10s\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].is_loaned ? "Yes" : "No"); // ternary operator - condition ? true : false
    }
}

void show_book_details(Book_t *library, int book_count, uint16_t id)
{
    for (int i = 0; i < book_count; i++)
    {
        if (library[i].id == id)
        {
            printf("Book Details:\n");
            printf("ID: %hu\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Loaned: %s\n", library[i].is_loaned ? "Yes" : "No");
            return;
        }
    }
    // If no matching book was found
    printf("No book found with ID %hu.\n", id);
}

void loan_book(Book_t *library, int book_count, uint16_t id)
{
    for (int i = 0; i < book_count; i++)
    {
        if (library[i].id == id) // Check if the current book's ID matches the provided ID
        {
            if (library[i].is_loaned) // Check if the book is already loaned
            {
                printf("Book with ID %hu is already loaned out.\n", id);
                // Prompt user for further action
                printf("Would you like to:\n");
                printf("1. Loan another book\n");
                printf("2. List available books\n");
                printf("3. Return to main menu\n");
                printf("Enter your choice: ");

                int choice;
                scanf("%d", &choice); // Read user's choice

                switch (choice)
                {
                case 1:
                    printf("Enter book ID to loan: ");
                    scanf("%hu", &id);                  // Read new book ID
                    loan_book(library, book_count, id); // Recursive call to loan another book
                    return;
                case 2:
                    list_available_books(library, book_count); // List available books
                    return;
                case 3:
                    return; // Return to main menu
                default:
                    printf("Invalid choice. Returning to main menu.\n");
                    return;
                }
            }
            library[i].is_loaned = true; // Mark the book as loaned
            printf("Book with ID %hu has been loaned successfully!\n", id);
            return; // Exit after loaning the book
        }
    }

    printf("No book found with ID %hu.\n", id);
}

void return_book(Book_t *library, int book_count, uint16_t id)
{
    for (int i = 0; i < book_count; i++)
    {
        if (library[i].id == id)
        {
            if (!library[i].is_loaned) // Check if the book is not loaned
            {
                printf("Book with ID %hu was not loaned out.\n", id);
                return; // Exit if the book was not loaned
            }

            library[i].is_loaned = false; // Mark the book as not loaned
            printf("Book with ID %hu has been returned successfully!\n", id);
            return;
        }
    }

    printf("No book found with ID %hu.\n", id);
}