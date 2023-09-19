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
int _strlen(const char *s);
const char *_strchr(const char *s, char c);

void _write_str(const char *str);
void _write_int(int num);
void _write_char(char c);
void _write_newline();
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
char *_strtok(char *str, const char *delim);

char *_strdup(const char *s);
int _atoi(char *str);
int _unsetenv(char *var);
int _setenv(char *var, char *value, int overwrite);
char *_getenv(char *name);
int _startswith(const char *str, const char *prefix);
void execute_command(char *command);
ssize_t _getline(char **lineptr, size_t *n, int fd);

int main(int argc, char *argv[]);

#endif /* MAIN_H */
