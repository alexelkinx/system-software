# Library Manager

## Table of Contents

- [Project Overview](#project-overview)
- [Directory Structure](#directory-structure)
- [Source Files](#source-files)
- [Getting Started](#getting-started)
- [Building the Project](#building-the-project)
- [Using the Program](#using-the-program)
- [Error Handling](#error-handling)

## Project Overview

In this lab, I created a simple **Library Manager** application in C that manages a collection of books. The program allows the user to perform several actions such as adding, deleting, and loaning books, as well as listing available books and searching for a book by ID. I also implemented file operations to save the state of the library to a file.

The project was built using a **Makefile** to manage the build process. I used **preprocessor directives** to conditionally include or exclude parts of the code.

### Key Features:

- **Library Management**: Add, delete, list, and manage books.
- **File Operations**: Save and load the library data from a file.
- **Makefile Build**: Used Makefile to control the build process.

## Directory Structure

```
lab-01-library-manager/
│
├── file_operations.c     # Functions for file I/O
├── file_operations.h     # File I/O function declarations
├── library.c             # Functions for managing books
├── library.csv           # Book database
├── library.h             # Library management functions
├── main.c                # Main program logic
├── Makefile              # Build configuration file
└── README.md             # Lab overview and instructions
```

## Source Files

### `main.c`

This file contains the entry point of the program. It includes the main loop where the user inputs commands to interact with the library system. The program uses a `switch-case` structure to handle various user commands, such as adding, deleting, and listing books.

### `library.c`

This file implements the functions for managing the books in the library. It contains functions to:

- Add a book
- Delete a book
- List all books
- List available books
- Loan a book
- Return a book
- Search for a book by ID

### `file_operations.c`

This file contains the functions for handling file operations. The program uses standard C file operations (`fopen`, `fclose`, `fgets`, `fprintf`) to save and load the library data to and from a file.

## Getting Started

### Prerequisites

Before running the main program, ensure that you have GCC (or another C compiler) installed on your system. You can check its version by running the following command:

```bash
gcc --version
```

### Building the Project

1. **Navigate to the project root directory:**

   ```bash
   cd lab-01-library-manager
   ```

2. **Compile the program using Makefile:**

   ```bash
   make
   ```

3. **Run the executable and provide a file name to load or create the library:**

   ```bash
   ./library_app library.csv
   ```

   If the file does not exist, the program will start with an empty library and create the file on exit. You can also use any file name without an extension, such as:

   ```bash
   ./library_app mylibrary
   ```

## Using the Program

The program accepts several commands to manage books in the library.

### Available Commands:

- `add`: Add a new book
- `del`: Delete a book
- `list`: List available books
- `lall`: List all books
- `lone`: List details of one book (search by ID)
- `loan`: Loan a book (search by ID)
- `return`: Return a book (search by ID)
- `exit`: Exit the program

Each command triggers the corresponding function to handle the request. The program operates in an infinite loop until the user exits.

### Example Usage:

Example session:

```bash
./library_app library.csv
```

Output:

```
Total books loaded: 14

Enter command (add, del, list, lall, lone, loan, return, exit): add
Enter book title: Animal Farm
Enter author name: George Orwell
Book added successfully with ID 15!

Enter command (add, del, list, lall, lone, loan, return, exit): add
Library is full. Cannot add more books.

Enter command (add, del, list, lall, lone, loan, return, exit): exit
Exiting program...
```

### File Operations

When the program is executed, it will ask for a file name, and any changes made to the library will be saved to that file. You can also load the library data from the file when the program starts.

A sample file `library.csv` is included in the project folder, containing initial book data. You can use it as a starting point or create your own.
The maximum number of books the library can hold is 15.

## Error Handling

The program checks for common errors, such as:

- Trying to loan a book that is already loaned.
- Trying to delete a non-existent book.
- File-related errors.

Detailed error messages are displayed when these issues occur.
