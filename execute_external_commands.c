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
    return cmd_path;
}

/**
 * execute_external_command - Executes an external cmd.
 *
 * @args:             An array of strings representing the cmd arguments.
 * @arg_c:        The number of arguments in the array.
 * @lastexit_status: Pointer to an integer containing the last exit status.
 */
void execute_external_command(char **args, int arg_c, int *lastexit_status)
{
    pid_t pid = fork(); /* Fork a child process */

    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        char *cmd_path = find_cmd_path(args[0]); /* Child process */

        if (cmd_path != NULL)
        {
            /* Build cmd_argv dynamically based on the number of arguments */
            char **cmd_argv = (char **)malloc((arg_c + 1) * sizeof(char *));
            int i;

			if (cmd_argv == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            for (i = 0; i < arg_c; i++)
            {
                cmd_argv[i] = args[i];
            }
            cmd_argv[arg_c] = NULL; /* NULL-terminate the array */

            if (execve(cmd_path, cmd_argv, environ) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }

            free(cmd_argv); /* Free dynamically allocated memory */
        }
        else
        {
            char msg[MAX_INPUT_SIZE]; /* Command not found in PATH */

            _write_str("Command not found: ");
            _write_str(args[0]);
            _write_newline();
            write(STDERR_FILENO, msg, _strlen(msg));
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status; /* Parent process */

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return;
        }

        if (WIFEXITED(status))
        {
            *lastexit_status = WEXITSTATUS(status);
        }
    }
}
