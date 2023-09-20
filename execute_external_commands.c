#include "main.h"

/**
 * find_command_path - Finds the path of an external command.
 *
 * @command: The name of the command to find.
 *
 * Return: A pointer to the command's path, or NULL if not found.
 */
char *find_command_path(char *command)
{
	/* Check if the command exists in one of the directories in PATH */
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path); /* Make a copy of PATH */
	char *dir = _strtok(path_copy, ":");
	char *command_path = NULL;

	while (dir != NULL)
	{
		/* Construct the full path to the command */
		char full_path[MAX_INPUT_SIZE];

		_write_str(dir);
		_write_char('/');
		_write_str(command);

		/* Check if the command exists in this directory */
		if (access(full_path, X_OK) == 0)
		{
			/* Command exists, set command_path and break */
			command_path = _strdup(full_path);
			break;
		}

		dir = _strtok(NULL, ":");
	}

	free(path_copy);
	return (command_path);
}


/**
 * execute_external_command - Executes an external command.
 *
 * @args:             An array of strings representing the command arguments.
 * @arg_count:        The number of arguments in the array.
 * @last_exit_status: Pointer to an integer containing the last exit status.
 */
void execute_external_command(char **args, int arg_count, int *last_exit_status)
{
	pid_t pid = fork();/* Fork a child process */

	if (pid == 0)
	{
		char *command_path = find_command_path(args[0]);/* Child process */

		if (command_path != NULL)
		{
			/* Execute command using full path,Adjust no of arguments as needed*/
			char *const command_argv[] = {command_path, args[0], args[1], args[2], NULL};

			if (execve(command_path, command_argv, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else
		{
			char msg[MAX_INPUT_SIZE];/* Command not found in PATH */

			_write_str("Command not found: ");
			_write_str(args[0]);
			_write_newline();
			write(STDERR_FILENO, msg, _strlen(msg));
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0)
	{
		perror("fork");
	} else
	{
		int status;/* Parent process */

		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			*last_exit_status = WEXITSTATUS(status);
		}
	}
}
