
#include "main.h"


/*  Define the alias list variable*/
struct AliasList *alias_list = NULL;

/**
 * main - The main entry point of the program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, or an error code on failure.
 */
int main(int argc, char *argv[])
{
	alias_list = create_alias_list();

	if (argc > 1)
	{
		/* Batch mode */
		return (batch_mode(argv[1]));
	}
	/* Interactive mode */
	return (interactive_mode());
}

/**
 * batch_mode - Handles batch mode execution by reading and executing commands
 *              from a specified file.
 *
 * @filename: The name of the batch file to read and execute commands from.
 *
 * Return: 0 on success, or an error code on failure.
 */
int batch_mode(char *filename)
{
	int file_fd = open(filename, O_RDONLY);

	if (file_fd == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}

	char *input = (char *)malloc(MAX_INPUT_SIZE);
	size_t input_size = MAX_INPUT_SIZE;
	ssize_t line_length;

	if (input == NULL)
	{
		perror("malloc");
		close(file_fd);
		return (EXIT_FAILURE);
	}

	while ((line_length = _getline(&input, &input_size, file_fd)) != -1)
	{
		input[line_length - 1] = '\0'; /*Remove newline character*/
		execute_command(input);
	}

	free(input);
	close(file_fd);
	return (0);
}

/**
 * interactive_mode - Handles interactive mode execution by reading and
 * executing commands entered by the user.
 *
 * Return: 0 on success, or an error code on failure.
 */
int interactive_mode(void)
{
	char *input = (char *)malloc(MAX_INPUT_SIZE);
	size_t input_size = MAX_INPUT_SIZE;
	ssize_t line_length;

	if (input == NULL)
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2); /* Use write to print the prompt */
		fflush(stdout);

		line_length = _getline(&input, &input_size, STDIN_FILENO);

		if (line_length == -1)
		{
			/* Handle end of file (Ctrl+D) */
			write(STDOUT_FILENO, "\n", 1);
			free(input);
			break;
		}

		input[line_length - 1] = '\0'; /* Remove newline character */
		execute_command(input);
	}

	free(input);
	return (0);
}
