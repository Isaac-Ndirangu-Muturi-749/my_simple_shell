#include "main.h"
#include "main2.h"
#include "main3.h"

/**
 * update_alias - Update an alias in the list.
 *
 * Parameters:
 * @list: The alias list in which the alias will be updated.
 * @name: The name of the alias to be updated.
 * @newval: The new value to assign to the alias.
 */
void update_alias(struct AliasList *list, const char *name, const char *newval)
{
	struct Alias *current = list->head;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = strdup(newval);
			return;
		}
		current = current->next;
	}
}

/**
 * execute_alias - Execute the "alias" built-in cmd.
 *
 * Parameters:
 * @list: The alias list in which to execute the cmd.
 * @args: An array of strings representing the cmd arguments.
 * @arg_c: The number of arguments in the array.
 */
void execute_alias(struct AliasList *list, char **args, int arg_c)
{
	int i;

	if (arg_c < 2)
	{
		_write_str("Usage: alias [name[='value'] ...]\n");
	}
	else
	{
		for (i = 1; i < arg_c; i++)
		{
			char *name = args[i];/* Split the argument into name and value */
			const char *value = strchr(args[i], '=');
			const char *existing_value;

			if (value == NULL)
			{
				value = "";/* If no '=' is present, set alias to an empty string */
			}
			else
			{
				value++; /* Move the value pointer past '=' */
			}
			/* Check if the alias already exists and update it, or add a new alias */
			existing_value = find_alias(list, name);
			if (existing_value != NULL)
			{
				update_alias(list, name, value);/* Alias exists, update its value */
			}
			else
			{
				add_alias(list, name, value);/* Alias doesn't exist, add a new alias */
			}
			_write_str("Setting alias: ");/* Print the alias */
			_write_str(name);
			_write_str("='");
			_write_str(value);
			_write_str("'\n");
		}
	}
}
