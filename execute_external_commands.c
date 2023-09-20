#include "main.h"

/**
 * find_cmd_path - Finds the path of an external cmd.
 *
 * @cmd: The name of the cmd to find.
 *
 * Return: A pointer to the cmd's path, or NULL if not found.
 */
char *find_cmd_path(char *cmd)
{
	/* Check if the cmd exists in one of the directories in PATH */
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path); /* Make a copy of PATH */
	char *dir = _strtok(path_copy, ":");
	char *cmd_path = NULL;

	while (dir != NULL)
	{
		/* Construct the full path to the cmd */
		char full_path[MAX_INPUT_SIZE];

		_write_str(dir);
		_write_char('/');
		_write_str(cmd);

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
 * execute_external_comand - Executes an external cmd.
 *
 * @args:             An array of strings representing the cmd arguments.
 * @arg_c:        The number of arguments in the array.
 * @lastexit_status: Pointer to an integer containing the last exit status.
 */
void execute_external_comand(char **args, int arg_c, int *lastexit_status)
{
	pid_t pid = fork();/* Fork a child process */

	if (pid == 0)
	{
		char *cmd_path = find_cmd_path(args[0]);/* Child process */

		if (cmd_path != NULL)
		{
			/* Execute cmd using full path,Adjust no of arguments as needed*/
			char *const cmd_argv[] = {cmd_path, args[0], args[1], args[2], NULL};

			if (execve(cmd_path, cmd_argv, environ) == -1)
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
			*lastexit_status = WEXITSTATUS(status);
		}
	}
}
