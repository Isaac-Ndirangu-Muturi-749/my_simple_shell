#include "main.h"

/**
 * update_alias - Update an alias in the list.
 *
 * Parameters:
 * @list: The alias list in which the alias will be updated.
 * @name: The name of the alias to be updated.
 * @new_value: The new value to assign to the alias.
 */
void update_alias(struct AliasList *list, const char *name, const char *new_value)
{
	struct Alias *current = list->head;

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
 * execute_alias - Execute the "alias" built-in command.
 *
 * Parameters:
 * @list: The alias list in which to execute the command.
 * @args: An array of strings representing the command arguments.
 * @arg_count: The number of arguments in the array.
 */
void execute_alias(struct AliasList *list, char **args, int arg_count)
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
				value++;/* Move the value pointer past '=' */
			}

			/* Check if the alias already exists and update it, or add a new alias */
			const char *existing_value = find_alias(list, name);

			if (existing_value != NULL)
			{
				/* Alias already exists, update its value */
				update_alias(list, name, value);
			} else
			{
				/* Alias doesn't exist, add a new alias */
				add_alias(list, name, value);
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
