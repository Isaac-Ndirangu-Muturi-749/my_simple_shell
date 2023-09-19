#include "main.h"

// Function to handle batch mode
int batch_mode(char *filename);
// Function to handle interactive mode
int interactive_mode();
int main(int argc, char *argv[]);

// Function to handle batch mode
int batch_mode(char *filename) {
    int file_fd = open(filename, O_RDONLY);
    if (file_fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    char *input = (char *)malloc(MAX_INPUT_SIZE);
    size_t input_size = MAX_INPUT_SIZE;
    ssize_t line_length;

    if (input == NULL) {
        perror("malloc");
        close(file_fd);
        return EXIT_FAILURE;
    }

    while ((line_length = _getline(&input, &input_size, file_fd)) != -1) {
        input[line_length - 1] = '\0'; // Remove newline character
        execute_command(input);
    }

    free(input);
    close(file_fd);
    return 0;
}

// Function to handle interactive mode
int interactive_mode() {
    char *input = (char *)malloc(MAX_INPUT_SIZE);
    size_t input_size = MAX_INPUT_SIZE;
    ssize_t line_length;

    if (input == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    while (1) {
        write(STDOUT_FILENO, "$ ", 2); // Use write to print the prompt
        fflush(stdout);

        line_length = _getline(&input, &input_size, STDIN_FILENO);

        if (line_length == -1) {
            // Handle end of file (Ctrl+D)
            write(STDOUT_FILENO, "\n", 1);
            free(input);
            break;
        }

        input[line_length - 1] = '\0'; // Remove newline character
        execute_command(input);
    }

    free(input);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // Batch mode
        return batch_mode(argv[1]);
    } else {
        // Interactive mode
        return interactive_mode();
    }
}
