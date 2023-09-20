#include "main.h"

/**
 * execute_command - Parses and executes a command given as a string.
 *
 * @command: The command string to be parsed and executed.
 *
 * Description: This function takes a command string and parses it into
 * individual arguments, then executes the specified command. It supports
 * built-in commands like "cd" and "exit" and also handles external commands.
 * The execution results are displayed on the standard output.
 */
void execute_command(char *command)
{
	if (command[0] == '\0')
	{
		return; /* Ignore empty commands */
	}

	/* Check if the command is a comment (starts with #) */
	if (command[0] == '#')
	{
		return; /* Ignore comments */
	}

	/* Variables for $? and $$ */
	int last_exit_status = 0; /* $? is initialized to 0 */
	pid_t shell_pid = getpid(); /* $$ is the shell's PID */

	/* Tokenize the command by semicolons into separate commands */
	char *commands[MAX_INPUT_SIZE];
	int command_count = 0;

	char *token = _strtok(command, ";");

	while (token != NULL)
	{
		commands[command_count++] = token;
		token = _strtok(NULL, ";");
	}

	for (int i = 0; i < command_count; i++)
	{
		execute_single_command(commands[i], &last_exit_status, shell_pid);
	}
}

/**
 * execute_single_command - Executes a single command string.
 *
 * @command: The command string to be executed.
 * @last_exit_status: A pointer to the variable that holds the exit status.
 * @shell_pid: The PID of the shell.
 *
 * Description: This function tokenizes a single command string into arguments,
 * handles variable replacement, and executes the command.
 */
void execute_single_command(char *command, int *last_exit_status, pid_t shell_pid)
{
	/* Tokenize the command into arguments */
	int arg_count = 0;
	char *args[MAX_INPUT_SIZE];

	char *token = _strtok(command, " ");

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = _strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	/* Handle variable replacement in arguments */
	handle_variable_replacement(args, arg_count, last_exit_status, shell_pid);

	/* Try to execute the command as a built-in, if not, execute externally */
	if (!execute_builtin_command(args, arg_count, last_exit_status))
	{
		execute_external_command(args, arg_count, last_exit_status);
	}
}
