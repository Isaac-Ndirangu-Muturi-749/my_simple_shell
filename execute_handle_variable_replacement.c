#include "main.h"

/**
 * var_replace - Handles variable replacement in cmd
 * arguments.
 *
 * @args:             An array of strings representing the cmd arguments.
 * @arg_c:        The number of arguments in the array.
 * @lastexit_status: Pointer to an integer containing the last exit status.
 * @shell_pid:        The process ID of the shell.
 *
 * Description: This function takes an array of cmd arguments and searches
 * for special variables (e.g., "$?", "$$") to replace with their corresponding
 * values. It also updates the last exit status. The modified arguments are
 * stored back in the 'args' array.
 */
void var_replace(char **args, int arg_c, int *lastexit_status, pid_t shell_pid)
{
	for (int j = 0; j < arg_c; j++)
	{
		if (_strcmp(args[j], "$?") == 0)
		{
			/* Replace $? with the last exit status */
			/* Assuming exit status can be represented in 10 digits */
			char exit_status_str[10];

			_write_int(*lastexit_status);
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
