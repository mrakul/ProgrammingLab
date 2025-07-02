#include <stdio.h>
#include <stdarg.h>

// A variadic arguments function
int my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}

int main() {
    // Declare a function pointer with variadic arguments
    int (*func_ptr)(const char *, ...);

    // Assign the function pointer to the variadic function
    func_ptr = my_printf;

    // Call the function through the pointer
    func_ptr("Hello, %s%d%s!", "world, and the number is: ", 10, " but this is the rest of the string\n");

    return 0;
}