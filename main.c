#include "shell.h"

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
	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
		interactive_mode(envp);
	else
		non_interactive_mode(envp);

	return (0);
}

/**
 * interactive_mode - Run the shell in interactive mode
 * @envp: Environment variables
 *
 * Return: void
 */
void interactive_mode(char **envp)
{
	char *command = NULL;
	int status = 1;

	while (status)
	{
		write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));
		command = read_line();

		if (command == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (_strlen(command) > 0)
			process_command(command, envp);

		free(command);
	}
}

/**
 * non_interactive_mode - Run the shell in non-interactive mode
 * @envp: Environment variables
 *
 * Return: void
 */
void non_interactive_mode(char **envp)
{
	char *command = NULL;

	while ((command = read_line()) != NULL)
	{
		if (_strlen(command) > 0)
			process_command(command, envp);

		free(command);
	}
}

/**
 * process_command - Process a command
 * @command: Command to process
 * @envp: Environment variables
 *
 * Return: void
 */
void process_command(char *command, char **envp)
{
	char **args = parse_command(command);

	if (args == NULL)
		return;

	if (args[0] != NULL)
	{
		if (is_builtin(args[0]))
			execute_builtin(args, envp);
		else
			execute_command(args, envp);
	}

	free_args(args);
}

