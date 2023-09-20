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

/* Declare environ */
extern char **environ;

// Structures
struct Alias {
    char *name;
    char *value;
    struct Alias *next;
};

struct AliasList {
    struct Alias *head;
};

// Global variables
extern struct AliasList *alias_list;
extern struct Alias *alias_head;

// Function declarations
struct AliasList* create_alias_list(void);
void add_alias(struct AliasList *list, const char *name, const char *value);
void print_aliases(const struct AliasList *list);
const char *find_alias(const struct AliasList *list, const char *name);
void update_alias(struct AliasList *list, const char *name, const char *newval);
void execute_alias(struct AliasList *list, char **args, int arg_c);
void *_memcpy(void *dest, const void *src, size_t n);
static int resize_buffer(char **lineptr, size_t *n);
ssize_t _getline(char **lineptr, size_t *n, int fd);
void execute_cmd(char *cmd, struct AliasList *alias_list);
void exec_one_cmd(char *cmd, int *lastexit_status, pid_t shell_pid, struct AliasList *alias_list);
void _write_str(const char *str);
void _write_int(int num);
void _write_char(char c);
void _write_newline(void);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strtok(char *str, const char *delim);
const char *_strchr(const char *s, char c);
int _strlen(const char *s);
char *_strdup(const char *s);
int _atoi(char *str);
int _startswith(const char *str, const char *prefix);
int _strncmp(const char *s1, const char *s2, size_t n);
int batch_mode(char *filename, struct AliasList *alias_list);
int interactive_mode(struct AliasList *alias_list);
int main(int argc, char *argv[]);
ssize_t _getline(char **lineptr, size_t *n, int fd);
void var_replace(char **args, int arg_c, int *lastexit_status, pid_t shell_pid);
char *find_cmd_path(char *cmd);
void execute_external_comand(char **args, int arg_c, int *lastexit_status);
int execute_exit(char **args, int arg_c);
int execute_cd(char **args, int arg_c);
int execute_setenv(char **args, int arg_c);
int execute_unsetenv(char **args, int arg_c);
int execute_env(void);
int exec_builtin_cmd(struct AliasList *alias_list, char **args, int arg_c, int *lastexit_status);
char *_getenv(char *name);
int _unsetenv(char *var);
size_t _getenv_len(const char *var);
void _add_env_var(const char *new_var);
int _setenv(const char *var, const char *value, int overwrite);

#endif /* MAIN_H */
