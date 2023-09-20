#include "main.h"

/**
* execute_exit - Executes the "exit" built-in command.
*
* @args: An array of strings representing the command arguments.
* @arg_count: The number of arguments in the array.
*
* Return: The exit status to be used for terminating the shell.
*
* Description: This function processes the "exit" built-in command, which
* terminates the shell. If no arguments are provided, it exits with a status
* of 0. If an argument is provided, it exits with the specified status.
*/
int execute_exit(char **args, int arg_count)
{
	if (arg_count > 1)
	{
		int exit_status = _atoi(args[1]);

		exit(exit_status);
	} else
	{
		exit(0);
	}
}

/**
 * execute_cd - Executes the "cd" built-in command.
 *
 * @args: An array of strings representing the command arguments.
 * @arg_count: The number of arguments in the array.
 *
 * Return: 0 on success, -1 on failure.
 *
 * Description: This function processes the "cd" built-in command,
 *  which changes the current working directory. If no arguments
 * are provided, it changes to the user's home directory. If an
 * argument is provided, it attempts to change to the specified directory.
 */
int execute_cd(char **args, int arg_count)
{
	if (arg_count > 1)
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	} else
	{
		chdir(_getenv("HOME"));
	}
}

/**
 * execute_setenv - Executes the "setenv" built-in command.
 *
 * @args: An array of strings representing the command arguments.
 * @arg_count: The number of arguments in the array.
 *
 * Return: 0 on success, -1 on failure.
 *
 * Description: This function processes the "setenv" built-in command, which sets
 * or updates an environment variable. If the variable doesn't exist, it creates
 * a new one.
 */
int execute_setenv(char **args, int arg_count)
{
	if (arg_count != 3)
	{
		char msg[] = "Usage: setenv VARIABLE VALUE\n";

		write(STDOUT_FILENO, msg, _strlen(msg));
	} else
	{
		char *variable = args[1];
		char *value = args[2];

		/* Set the environment variable (custom implementation or use _setenv) */
		if (_setenv(variable, value, 1) != 0)
		{
			perror("setenv");
		}
	}
}

/**
 * execute_unsetenv - Executes the "unsetenv" built-in command.
 *
 * @args: An array of strings representing the command arguments.
 * @arg_count: The number of arguments in the array.
 *
 * Return: 0 on success, -1 on failure.
 *
 * Description: This function processes the "unsetenv" built-in command, which
 * removes an environment variable.
 */
int execute_unsetenv(char **args, int arg_count)
{
	if (arg_count != 2)
	{
		char msg[] = "Usage: unsetenv VARIABLE\n";

		write(STDOUT_FILENO, msg, _strlen(msg));
	} else
	{
		char *variable = args[1];

		/* Unset the environment variable (custom implementation or use _unsetenv) */
		if (_unsetenv(variable) != 0)
		{
			perror("unsetenv");
		}
	}
}

/**
 * execute_env - Executes the "env" built-in command.
 *
 * Description: This function processes the "env" built-in command, which prints
 * the current environment.
 *
 * Return: Always returns 0.
 */
int execute_env(void)
{
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * execute_builtin_command - Executes built-in commands.
 *
 * @args: An array of strings representing the command arguments.
 * @arg_count: The number of arguments in the array.
 * @last_exit_status: Pointer to an integer containing the last exit status.
 *
 * Return: The exit status of the executed built-in command.
 *
 * Description: This function processes and executes various built-in commands,
 * such as "exit," "cd," "setenv," "unsetenv," and "env."
 */
int execute_builtin_command(char **args, int arg_count, int *last_exit_status)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		execute_exit(args, arg_count);
	} else if (_strcmp(args[0], "cd") == 0)
	{
		execute_cd(args, arg_count);
	} else if (_strcmp(args[0], "alias") == 0)
	{
		execute_alias(args, arg_count);
	} else if (_strcmp(args[0], "setenv") == 0)
	{
		execute_setenv(args, arg_count);
	} else if (_strcmp(args[0], "unsetenv") == 0)
	{
		execute_unsetenv(args, arg_count);
	} else if (_strcmp(args[0], "env") == 0)
	{
		execute_env();
	} else
	{
		return (0); /* Not a built-in command */
	}

	return (1); /* Command was a built-in */
}
