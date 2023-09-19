#include "main.h"

// Function to handle variable replacement in arguments
void handle_variable_replacement(char **args, int arg_count, int *last_exit_status, pid_t shell_pid);

// Function to handle variable replacement in arguments
void handle_variable_replacement(char **args, int arg_count, int *last_exit_status, pid_t shell_pid) {
    for (int j = 0; j < arg_count; j++) {
        if (_strcmp(args[j], "$?") == 0) {
            // Replace $? with the last exit status
            char exit_status_str[10]; // Assuming exit status can be represented in 10 digits
            _write_int(*last_exit_status);
            char *new_arg = _strdup(exit_status_str);
            if (new_arg == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            args[j] = new_arg;
        } else if (_strcmp(args[j], "$$") == 0) {
            // Replace $$ with the shell's PID
            char shell_pid_str[10]; // Assuming PID can be represented in 10 digits
            _write_int(shell_pid);
            char *new_arg = _strdup(shell_pid_str);
            if (new_arg == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            args[j] = new_arg;
        }
    }
}