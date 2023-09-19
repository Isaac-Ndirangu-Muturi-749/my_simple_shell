#include "main.h"

// Custom _getline function
ssize_t _getline(char **lineptr, size_t *n, int fd);

// Custom _getline function
ssize_t _getline(char **lineptr, size_t *n, int fd) {
    ssize_t bytesRead = 0;
    ssize_t totalBytesRead = 0;
    char *line = *lineptr;

    if (line == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    while (1) {
        // Check if we need to allocate more memory
        if (totalBytesRead >= *n) {
            size_t new_size = (*n == 0) ? 128 : *n * 2;
            char *new_line = realloc(*lineptr, new_size);
            if (new_line == NULL) {
                return -1; // Memory allocation error
            }
            *lineptr = new_line;
            *n = new_size;
            line = *lineptr + totalBytesRead;
        }

        // Read a single character from the file descriptor
        bytesRead = read(fd, line, 1);

        // Check for errors or end of file
        if (bytesRead == -1) {
            return -1; // Error reading
        } else if (bytesRead == 0) {
            if (totalBytesRead == 0) {
                return -1; // No data read (EOF)
            }
            break; // End of line
        }

        // Move the line pointer and update the total bytes read
        line += bytesRead;
        totalBytesRead += bytesRead;

        // Check if we've reached the end of the line
        if (*(line - 1) == '\n') {
            break;
        }
    }

    // Null-terminate the line
    *line = '\0';

    return totalBytesRead;
}
