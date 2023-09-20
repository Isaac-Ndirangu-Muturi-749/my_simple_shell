#include "main.h"

/**
 * handle_variable_replacement - Handles variable replacement in command
 * arguments.
 *
 * @args:             An array of strings representing the command arguments.
 * @arg_count:        The number of arguments in the array.
 * @last_exit_status: Pointer to an integer containing the last exit status.
 * @shell_pid:        The process ID of the shell.
 *
 * Description: This function takes an array of command arguments and searches
 * for special variables (e.g., "$?", "$$") to replace with their corresponding
 * values. It also updates the last exit status. The modified arguments are
 * stored back in the 'args' array.
 */
void handle_variable_replacement(char **args, int arg_count, int *last_exit_status, pid_t shell_pid)
{
	for (int j = 0; j < arg_count; j++)
	{
		if (_strcmp(args[j], "$?") == 0)
		{
			/* Replace $? with the last exit status */
			/* Assuming exit status can be represented in 10 digits */
			char exit_status_str[10];

			_write_int(*last_exit_status);
			char *new_arg = _strdup(exit_status_str);

			if (new_arg == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			args[j] = new_arg;
		}
		else if (_strcmp(args[j], "$$") == 0)
		{
			/* Replace $$ with the shell's PID */
			/* Assuming PID can be represented in 10 digits */
			char shell_pid_str[10];

			_write_int(shell_pid);
			char *new_arg = _strdup(shell_pid_str);

			if (new_arg == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			args[j] = new_arg;
		}
	}
}
