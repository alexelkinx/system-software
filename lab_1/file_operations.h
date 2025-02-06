#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "library.h"

void load_books_from_file(Book_t *library, int *book_count, const char *filename);
void save_books_to_file(Book_t *library, int book_count, const char *filename);

#endif