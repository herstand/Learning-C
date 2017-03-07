# C Practice
C Programming Practice
Compiled using `gcc -std=c11 -pedantic-errors file_name.c [other_file.c, …]`

## Projects
* [Hello World](#hello-world)
* [Verify User Input](#verify-user-input)
* [Age Comparer](#age-comparer)

## Hello World

### Description
Prints "Hello, world!" to the screen (duh)

### Standard functions used:
* printf()

## Verify User Input

### Description
Prompts the user for a positive integer, validates input and responds appropriately.

### Standard functions used:
* printf()
* strtol()
* strlen()
* getchar()

### Concepts Utilized
* header files
* compiling multiple c files at once
* error handling in c (via parameter passing)
* pass by reference (via pointer passing)
* strings (explicitly setting '\0' to mark end of char array)
* dereferencing (using & symbol)

## Age Comparer

### Description
Compares user's age with programmer's age.

### Standard functions used:
* getchar()
* strtol()
* printf()

### TODO
* Error handling
* Split into multiple functions