#include "main.h"
#include "main2.h"
#include "main3.h"

/**
 * find_cmd_path - Finds the path of an external cmd.
 *
 * @cmd: The name of the cmd to find.
 *
 * Return: A pointer to the cmd's path, or NULL if not found.
 */
char *find_cmd_path(char *cmd)
{
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path); /* Make a copy of PATH */
	char *dir = _strtok(path_copy, ":");
	char *cmd_path = NULL;

	while (dir != NULL)
	{
		char full_path[MAX_INPUT_SIZE];

		/* Construct the full path to the cmd */
		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, cmd);

		/* Check if the cmd exists in this directory */
		if (access(full_path, X_OK) == 0)
		{
			/* Command exists, set cmd_path and break */
			cmd_path = _strdup(full_path);
			break;
		}

		dir = _strtok(NULL, ":");
	}

	free(path_copy);
	return (cmd_path);
}

/**
 * execute_external_command - Executes an external command.
 *
 * @args: An array of strings representing the command arguments.
 * @arg_c: The number of arguments in the array.
 * @lastexit_status: Pointer to an integer containing the last exit status.
 */
void execute_external_command(char **args, int arg_c, int *lastexit_status)
{
	pid_t pid = fork_child_process();

	if (pid == 0)
	{
		execute_command(args, arg_c);
	} else
	{
		wait_for_child_process(pid, lastexit_status);
	}
}


/**
 * fork_child_process - Forks a child process and returns the process ID.
 *
 * Return: The process ID of the child process.
 */
pid_t fork_child_process(void)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

/**
 * execute_command - Executes the command using the execve system call.
 *
 * @args: An array of strings representing the command arguments.
 * @arg_c: The number of arguments in the array.
 */
void execute_command(char **args, int arg_c)
{
	char *cmd_path = find_cmd_path(args[0]);

	if (cmd_path != NULL)
	{
		char **cmd_argv = build_command_arguments(args, arg_c);

		if (execve(cmd_path, cmd_argv, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(cmd_argv);
	} else
	{
		handle_command_not_found(args[0]);
	}
}


