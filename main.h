#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024

// Declare environ
extern char **environ;

// Function declarations

// Custom _write_str function for string formatting
void _write_str(const char *str);
// Custom _write_int function for formatting integers
void _write_int(int num);
// Custom _write_char function for writing a single character
void _write_char(char c);
// Custom _write_newline function for writing a newline character
void _write_newline();
// Custom _startswith function
int _startswith(const char *str, const char *prefix);

// Custom _strcpy function
char *_strcpy(char *dest, const char *src);
// Custom _strcat function
char *_strcat(char *dest, const char *src);
// Custom _strcmp function
int _strcmp(char *s1, char *s2);
// Custom _strtok function
char *_strtok(char *str, const char *delim);
// Custom _strchr function
const char *_strchr(const char *s, char c);
// Custom _strlen function
int _strlen(const char *s);
// Custom _strdup function
char *_strdup(const char *s);
// Custom _atoi function
int _atoi(char *str);

// Function to handle batch mode
int batch_mode(char *filename);
// Function to handle interactive mode
int interactive_mode();
int main(int argc, char *argv[]);

// Custom _getline function
ssize_t _getline(char **lineptr, size_t *n, int fd);

// Function to parse and execute a command
void execute_command(char *command);

// Function to handle variable replacement in arguments
void handle_variable_replacement(char **args, int arg_count, int *last_exit_status, pid_t shell_pid);

// Function to find the path of an external command
char* find_command_path(char *command);
// Function to execute an external command
void execute_external_command(char **args, int arg_count, int *last_exit_status);

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

// Custom _getenv function
char *_getenv(char *name);
// Custom _setenv function
int _setenv(char *var, char *value, int overwrite);
// Custom _unsetenv function
int _unsetenv(char *var);

// Define a structure to represent an alias
struct Alias {
    char *name;
    char *value;
    struct Alias *next;
};
// Global pointer to the head of the alias linked list
extern struct Alias *alias_head;
// Function to add an alias to the linked list
void add_alias(const char *name, const char *value);
// Function to print all aliases
void print_aliases();
// Function to find an alias by name and return its value
const char *find_alias(const char *name);
// Function to update an alias with a new value
void update_alias(const char *name, const char *new_value);
// Function to handle the "alias" built-in command
void execute_alias(char **args, int arg_count);

#endif /* MAIN_H */












