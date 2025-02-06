# Define the compiler (gcc is the GNU Compiler Collection)
CC = gcc

# Compiler flags:
# -Wall: Enables all compiler's warning messages
# -Wextra: Enables extra warning messages
# -std=c99: Use the C99 standard
# -g: Enables debugging information (not used in this build)
CFLAGS = -Wall -Wextra -std=c99

# The name of the final executable file
TARGET = library_app

# List of source files
SRCS = main.c library.c file_operations.c

# Convert the list of source files into a list of object files (.o)
# $(SRCS:.c=.o) means replace ".c" with ".o" in the SRCS list
# Separates compilation, as only changed source files need to be recompiled
OBJS = $(SRCS:.c=.o)

# Default target that builds the executable when we run 'make'
all: $(TARGET)

# Target that links all object files and produces the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Target to remove the executable and all object files
clean:
	rm -f $(TARGET) *.o

# A target to run the program with a default library file
run: $(TARGET) # Compile the program and run it passing library.csv as an argument
	./$(TARGET) library.csv