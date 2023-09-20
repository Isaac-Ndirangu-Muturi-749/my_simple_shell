#include "main.h"

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
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		execute_cd(args, arg_count);
	}
	else if (_strcmp(args[0], "alias") == 0)
	{
		execute_alias(alias_list, args, arg_count);
	}
	else if (_strcmp(args[0], "setenv") == 0)
	{
		execute_setenv(args, arg_count);
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		execute_unsetenv(args, arg_count);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		execute_env();
	}
	else
	{
		return (0); /* Not a built-in command */
	}

	return (1); /* Command was a built-in */
}