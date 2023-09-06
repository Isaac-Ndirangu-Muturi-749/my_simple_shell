int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];

    if (argc > 1) {
        // Batch mode: read commands from a file using open
        int file_descriptor = open(argv[1], O_RDONLY);
        if (file_descriptor == -1) {
            perror("open");
            return EXIT_FAILURE;
        }

        char *input = NULL;
        size_t input_size = 0;
        ssize_t line_length;

        while ((line_length = getline(&input, &input_size, file_descriptor)) != -1) {
            input[line_length - 1] = '\0'; // Remove newline character
            execute_command(input);
        }

        close(file_descriptor);
        free(input);
    } else {
        // Interactive mode: read commands from user input using write and getline
        char *input = NULL;
        size_t input_size = 0;
        ssize_t line_length;

        while (1) {
            write(STDOUT_FILENO, "$ ", 2); // Use write to print the prompt
            fflush(stdout);

            line_length = getline(&input, &input_size, stdin);

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
    }

    return 0;
}


