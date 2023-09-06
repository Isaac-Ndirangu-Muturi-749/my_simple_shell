#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

// Function to parse and execute a command
void execute_command(char *command) {
    char *args[MAX_INPUT_SIZE];
    int arg_count = 0;

    // Tokenize the command into arguments
    char *token = strtok(command, " ");
    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    // Handle built-in commands
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (arg_count > 1) {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        } else {
            chdir(getenv("HOME"));
        }
    } else if (strcmp(args[0], "alias") == 0) {
        // Handle alias command (not implemented in this example)
        // You can implement alias handling here
    } else if (strcmp(args[0], "setenv") == 0) {
        // Handle setenv command (not implemented in this example)
        // You can implement environment variable setting here
    } else if (strcmp(args[0], "unsetenv") == 0) {
        // Handle unsetenv command (not implemented in this example)
        // You can implement environment variable unsetting here
    } else {
        // Fork a child process
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("shell");
                exit(EXIT_FAILURE);
            }
        } else if (pid < 0) {
            perror("fork");
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            }
        }
    }
}
