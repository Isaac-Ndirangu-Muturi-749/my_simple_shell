#include "main.h"

// Custom _getenv function
char *_getenv(char *name);
// Custom _setenv function
int _setenv(char *var, char *value, int overwrite);
// Custom _unsetenv function
int _unsetenv(char *var);


// Custom _getenv function
char *_getenv(char *name) {
    char **environ_ptr = environ;
    while (*environ_ptr) {
        if (_startswith(*environ_ptr, name)) {
            return *environ_ptr;
        }
        environ_ptr++;
    }
    return NULL; // Variable not found
}

// Custom _setenv function
int _setenv(char *var, char *value, int overwrite) {
    char **environ_ptr = environ;
    if (!var || !value || !environ_ptr) {
        return 0;
    }

    // Create a new environment variable string in the format "var=value"
    int new_var_length = _strlen(var) + _strlen(value) + 2;
    char *new_var = (char *)malloc(new_var_length);
    if (!new_var) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Construct the new environment variable string using custom write-based functions
    char *ptr = new_var;
    _strcpy(ptr, var);
    ptr += _strlen(var);
    _write_char('=');
    _strcpy(ptr, value);

    int index = 0;
    while (environ_ptr[index] != NULL) {
        if (_startswith(environ_ptr[index], var) && environ_ptr[index][_strlen(var)] == '=') {
            // Modify an existing variable
            free(environ_ptr[index]);
            environ_ptr[index] = new_var;
            return 0;
        }
        index++;
    }

    // If the variable doesn't exist, add it to the environment
    // Find the number of environment variables
    int env_count = 0;
    while (environ_ptr[env_count] != NULL) {
        env_count++;
    }

    // Allocate memory for a new environment with space for the new variable
    char **new_environ = (char **)malloc((env_count + 2) * sizeof(char *));
    if (!new_environ) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copy the old environment variables
    for (int i = 0; i < env_count; i++) {
        new_environ[i] = environ_ptr[i];
    }

    // Add the new variable to the end
    new_environ[env_count] = new_var;
    new_environ[env_count + 1] = NULL;

    // Update the environment pointer
    environ = new_environ;

    return 0;
}

// Custom _unsetenv function
int _unsetenv(char *var) {
    char **environ_ptr = environ;

    if (!environ_ptr || !var) {
        return 0;
    }

    int index = 0;
    while (environ_ptr[index] != NULL) {
        if (_startswith(environ_ptr[index], var) && environ_ptr[index][_strlen(var)] == '=') {
            // Remove the entry by shifting all entries after it
            for (int i = index; environ_ptr[i] != NULL; i++) {
                environ_ptr[i] = environ_ptr[i + 1];
            }
            return 1; // Indicates successful deletion
        }
        index++;
    }

    return 0; // Indicates variable not found
}