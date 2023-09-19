#include "main.h"

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

// Define the global alias_head variable
struct Alias *alias_head = NULL;


// Function to add an alias to the linked list
void add_alias(const char *name, const char *value) {
    struct Alias *new_alias = (struct Alias *)malloc(sizeof(struct Alias));
    if (new_alias == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = NULL;

    if (alias_head == NULL) {
        alias_head = new_alias;
    } else {
        struct Alias *current = alias_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_alias;
    }
}

// Function to print all aliases
void print_aliases() {
    struct Alias *current = alias_head;
    while (current != NULL) {
        _write_str("Setting alias: ");
        _write_str(current->name);
        _write_str("='");
        _write_str(current->value);
        _write_str("'\n");
        current = current->next;
    }
}

// Function to find an alias by name and return its value
const char *find_alias(const char *name) {
    struct Alias *current = alias_head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // Alias not found
}

// Function to update an alias with a new value
void update_alias(const char *name, const char *new_value) {
    struct Alias *current = alias_head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            free(current->value);
            current->value = strdup(new_value);
            return;
        }
        current = current->next;
    }
}

// Function to handle the "alias" built-in command
void execute_alias(char **args, int arg_count) {
    if (arg_count < 2) {
        _write_str("Usage: alias [name[='value'] ...]\n");
    } else {
        for (int i = 1; i < arg_count; i++) {
            // Split the argument into name and value
            char *name = args[i];
            const char *value = strchr(args[i], '=');

            if (value == NULL) {
                // If no '=' is present, set alias to an empty string
                value = "";
            } else {
                // Move the value pointer past '='
                value++;
            }

            // Check if the alias already exists and update it, or add a new alias
            const char *existing_value = find_alias(name);
            if (existing_value != NULL) {
                // Alias already exists, update its value
                update_alias(name, value);
            } else {
                // Alias doesn't exist, add a new alias
                add_alias(name, value);
            }

            // Print the alias
            _write_str("Setting alias: ");
            _write_str(name);
            _write_str("='");
            _write_str(value);
            _write_str("'\n");
        }
    }
}
