#include "main.h"


/**
 * execute_cmd - Parses and executes a cmd given as a string.
 *
 * @cmd: The cmd string to be parsed and executed.
 * @alias_list: A pointer to the AliasList structure.
 *
 * Description: This function takes a cmd string and parses it into
 * individual arguments, then executes the specified cmd. It supports
 * built-in cmds like "cd" and "exit" and also handles external cmds.
 * The execution results are displayed on the standard output.
 */
void execute_cmd(char *cmd, struct AliasList *alias_list)
{
	if (cmd[0] == '\0')
	{
		return; /* Ignore empty cmds */
	}

	/* Check if the cmd is a comment (starts with #) */
	if (cmd[0] == '#')
	{
		return; /* Ignore comments */
	}

	/* Variables for $? and $$ */
	int lastexit_status = 0; /* $? is initialized to 0 */
	pid_t shell_pid = getpid(); /* $$ is the shell's PID */

	/* Tokenize the cmd by semicolons into separate cmds */
	char *cmds[MAX_INPUT_SIZE];
	int cmd_count = 0;

	char *token = _strtok(cmd, ";");

	while (token != NULL)
	{
		cmds[cmd_count++] = token;
		token = _strtok(NULL, ";");
	}

	for (int i = 0; i < cmd_count; i++)
	{
		exec_one_cmd(cmds[i], &lastexit_status, shell_pid, alias_list);
	}
}

/**
 * exec_one_cmd - Executes a single cmd string.
 *
 * @cmd: The cmd string to be executed.
 * @lastexit_status: A pointer to the variable that holds the exit status.
 * @shell_pid: The PID of the shell.
 * @alias_list: A pointer to the AliasList structure.
 *
 * Description: This function tokenizes a single cmd string into arguments,
 * handles variable replacement, and executes the cmd.
 */
void exec_one_cmd(char *cmd, int *lastexit_status, pid_t shell_pid, struct AliasList *alias_list)
{
	/* Tokenize the cmd into arguments */
	int arg_c = 0;
	char *args[MAX_INPUT_SIZE];

	char *token = _strtok(cmd, " ");

	while (token != NULL)
	{
		args[arg_c++] = token;
		token = _strtok(NULL, " ");
	}
	args[arg_c] = NULL;

	/* Handle variable replacement in arguments */
	var_replace(args, arg_c, lastexit_status, shell_pid);

	/* Try to execute the cmd as a built-in, if not, execute externally */
	if (!exec_builtin_cmd(alias_list, args, arg_c, lastexit_status))
	{
		execute_external_comand(args, arg_c, lastexit_status);
	}
}
