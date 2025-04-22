#include "shell.h"

static int last_exit_status = 0;

/**
 * main - Entry point for the simple shell program
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: Exit status of the shell
 */
int main(int argc, char **argv, char **envp)
{
	int last_status = 0;
	(void)argc;

	if (isatty(STDIN_FILENO))
		interactive_mode(envp, argv[0], &last_status);
	else
		non_interactive_mode(envp, argv[0], &last_status);

	return (last_status);
}

/**
 * interactive_mode - Run the shell in interactive mode
 * @envp: Environment variables
 * @program_name: Name of the program
 * @last_status: Pointer to the last exit status
 *
 * Return: void
 */
void interactive_mode(char **envp, char *program_name, int *last_status)
{
	char *command = NULL;

	while (1)
	{
		write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));
		command = read_line();

		if (command == NULL) /* EOF (Ctrl+D) */
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (_strlen(command) > 0)
			*last_status = process_command(command, envp, program_name);

		free(command);
	}
}

/**
 * non_interactive_mode - Run the shell in non-interactive mode
 * @envp: Environment variables
 * @program_name: Name of the program
 * @last_status: Pointer to the last exit status
 *
 * Return: void
 */
void non_interactive_mode(char **envp, char *program_name, int *last_status)
{
	char *command = NULL;

	while ((command = read_line()) != NULL)
	{
		if (_strlen(command) > 0)
			*last_status = process_command(command, envp, program_name);

		free(command);
	}
}

/**
 * process_command - Process a command line
 * @command: Raw input string
 * @envp: Environment variables
 * @program_name: Name of the shell executable
 *
 * Return: Exit status of the command
 */
int process_command(char *command, char **envp, char *program_name)
{
	char **args = parse_command(command);
	int status = 0;

	if (args == NULL)
		return (0);

	if (args[0] != NULL)
	{
		if (_strcmp(args[0], "exit") == 0)
		{
			free_args(args);
			free(command);
			exit(last_exit_status);
		}

		if (is_builtin(args[0]))
			status = execute_builtin(args, envp);
		else
			status = execute_command(args, envp, program_name);
	}

	free_args(args);
	last_exit_status = status;
	return (status);
}
