#include "main.h"

// Function to execute the "exit" built-in command
int execute_exit(char **args, int arg_count);
// Function to execute the "cd" built-in command
int execute_cd(char **args, int arg_count);
// Function to execute the "setenv" built-in command
int execute_setenv(char **args, int arg_count);
// Function to execute the "unsetenv" built-in command
int execute_unsetenv(char **args, int arg_count);
// Function to execute the "env" built-in command
int execute_env();
// Function to execute built-in commands
int execute_builtin_command(char **args, int arg_count, int *last_exit_status);


// Function to execute the "exit" built-in command
int execute_exit(char **args, int arg_count) {
    if (arg_count > 1) {
        int exit_status = _atoi(args[1]);
        exit(exit_status);
    } else {
        exit(0);
    }
}

// Function to execute the "cd" built-in command
int execute_cd(char **args, int arg_count) {
    if (arg_count > 1) {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    } else {
        chdir(_getenv("HOME"));
    }
}

// Function to execute the "setenv" built-in command
int execute_setenv(char **args, int arg_count) {
    if (arg_count != 3) {
        char msg[] = "Usage: setenv VARIABLE VALUE\n";
        write(STDOUT_FILENO, msg, _strlen(msg));
    } else {
        char *variable = args[1];
        char *value = args[2];

        // Set the environment variable (custom implementation or use _setenv)
        if (_setenv(variable, value, 1) != 0) {
            perror("setenv");
        }
    }
}

// Function to execute the "unsetenv" built-in command
int execute_unsetenv(char **args, int arg_count) {
    if (arg_count != 2) {
        char msg[] = "Usage: unsetenv VARIABLE\n";
        write(STDOUT_FILENO, msg, _strlen(msg));
    } else {
        char *variable = args[1];

        // Unset the environment variable (custom implementation or use _unsetenv)
        if (_unsetenv(variable) != 0) {
            perror("unsetenv");
        }
    }
}

// Function to execute the "env" built-in command
int execute_env() {
    char **env = environ;
    while (*env) {
        write(STDOUT_FILENO, *env, _strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}

// Function to execute built-in commands
int execute_builtin_command(char **args, int arg_count, int *last_exit_status) {
    if (_strcmp(args[0], "exit") == 0) {
        execute_exit(args, arg_count);
    } else if (_strcmp(args[0], "cd") == 0) {
        execute_cd(args, arg_count);
    } else if (_strcmp(args[0], "alias") == 0) {
        execute_alias(args, arg_count);
    } else if (_strcmp(args[0], "setenv") == 0) {
        execute_setenv(args, arg_count);
    } else if (_strcmp(args[0], "unsetenv") == 0) {
        execute_unsetenv(args, arg_count);
    } else if (_strcmp(args[0], "env") == 0) {
        execute_env();
    } else {
        return 0; // Not a built-in command
    }

    return 1; // Command was a built-in
}
