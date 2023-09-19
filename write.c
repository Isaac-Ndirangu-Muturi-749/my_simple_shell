
#include <main.h>

// Custom _write_str function for string formatting
void _write_str(const char *str) {
    write(STDOUT_FILENO, str, _strlen(str));
}

// Custom _write_int function for formatting integers
void _write_int(int num) {
    char buffer[20]; // Assuming a reasonable buffer size
    int length = 0;
    int temp = num;

    // Handle negative numbers
    if (temp < 0) {
        _write_char('-');
        temp = -temp;
    }

    // Convert the integer to a string in reverse order
    do {
        buffer[length++] = temp % 10 + '0';
        temp /= 10;
    } while (temp > 0);

    // Reverse the string to get the correct order
    for (int i = 0, j = length - 1; i < j; i++, j--) {
        char tmp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = tmp;
    }

    write(STDOUT_FILENO, buffer, length);
}


// Custom _write_char function for writing a single character
void _write_char(char c) {
    write(STDOUT_FILENO, &c, 1);
}

// Custom _write_newline function for writing a newline character
void _write_newline() {
    char newline = '\n';
    write(STDOUT_FILENO, &newline, 1);
}