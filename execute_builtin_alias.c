
#include "main.h"

/* Define the global alias_head variable */
struct Alias *alias_head = NULL;

/**
 * add_alias - Adds an alias to the linked list of aliases.
 *
 * @name: The name of the alias to be added.
 * @value: The value of the alias.
 *
 * Description: This function adds a new alias to the linked list of aliases,
 * storing its name and value.
 */
void add_alias(const char *name, const char *value)
{
	struct Alias *new_alias = (struct Alias *)malloc(sizeof(struct Alias));

	if (new_alias == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = NULL;

	if (alias_head == NULL)
	{
		alias_head = new_alias;
	} else
	{
		struct Alias *current = alias_head;

		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_alias;
	}
}

/**
 * print_aliases - Prints all aliases in the format name='value'.
 *
 * Description: This function prints all aliases, one per line, in the format
 * name='value'.
 */
void print_aliases(void)
{
	struct Alias *current = alias_head;

	while (current != NULL)
	{
		_write_str("Setting alias: ");
		_write_str(current->name);
		_write_str("='");
		_write_str(current->value);
		_write_str("'\n");
		current = current->next;
	}
}

/**
 * find_alias - Finds an alias by name and returns its value.
 *
 * @name: The name of the alias to find.
 *
 * Return: The value of the alias if found, or NULL if not found.
 *
 * Description: This function searches for an alias by its name and returns its
 * value. If the alias is not found, it returns NULL.
 */
const char *find_alias(const char *name)
{
	struct Alias *current = alias_head;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL); /* Alias not found */
}

/**
 * update_alias - Updates an existing alias with a new value.
 *
 * @name: The name of the alias to be updated.
 * @new_value: The new value to assign to the alias.
 *
 * Description: This function searches for an existing alias by its name and
 * updates its value with the provided new value.
 */
void update_alias(const char *name, const char *new_value)
{
	struct Alias *current = alias_head;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = strdup(new_value);
			return;
		}
		current = current->next;
	}
}

/**
 * execute_alias - Handles the "alias" built-in command.
 *
 * @args: An array of strings representing the command arguments.
 * @arg_count: The number of arguments in the array.
 *
 * Description: This function processes the "alias" built-in command, which is
 * used to set or display aliases. It can define new aliases or print existing
 * aliases.
 */
void execute_alias(char **args, int arg_count)
{
	if (arg_count < 2)
	{
		_write_str("Usage: alias [name[='value'] ...]\n");
	} else
	{
		for (int i = 1; i < arg_count; i++)
		{
			/* Split the argument into name and value */
			char *name = args[i];
			const char *value = strchr(args[i], '=');

			if (value == NULL)
			{
				/* If no '=' is present, set alias to an empty string */
				value = "";
			} else
			{
				/* Move the value pointer past '=' */
				value++;
			}

			/* Check if the alias already exists and update it, or add a new alias */
			const char *existing_value = find_alias(name);

			if (existing_value != NULL)
			{
				/* Alias already exists, update its value */
				update_alias(name, value);
			} else
			{
				/* Alias doesn't exist, add a new alias */
				add_alias(name, value);
			}

			/* Print the alias */
			_write_str("Setting alias: ");
			_write_str(name);
			_write_str("='");
			_write_str(value);
			_write_str("'\n");
		}
	}
}
