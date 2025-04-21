#include "shell.h"

/**
 * is_builtin - Check if command is a built-in
 * @command: Command to check
 *
 * Return: 1 if command is a built-in, 0 otherwise
 */
int is_builtin(char *command)
{
	int i;
	char *builtins[] = {"exit", "env", NULL};

	if (command == NULL)
		return (0);

	for (i = 0; builtins[i] != NULL; i++)
	{
		if (_strcmp(command, builtins[i]) == 0)
			return (1);
	}

	return (0);
}

/**
 * execute_builtin - Execute built-in command
 * @args: Array of arguments
 * @envp: Environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int execute_builtin(char **args, char **envp)
{
	builtin_t builtins[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{NULL, NULL}
	};
	int i;

	if (args == NULL || args[0] == NULL)
		return (0);

	for (i = 0; builtins[i].name != NULL; i++)
	{
		if (_strcmp(args[0], builtins[i].name) == 0)
			return (builtins[i].func(args, envp));
	}

	return (0);
}

/**
 * builtin_exit - Implement exit built-in command
 * @args: Array of arguments
 * @envp: Environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int builtin_exit(char **args, char **envp)
{
	(void)args;
	(void)envp;

	exit(0);
}

/**
 * builtin_env - Implement env built-in command
 * @args: Array of arguments
 * @envp: Environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int builtin_env(char **args, char **envp)
{
	int i;
	(void)args;

	if (envp == NULL)
		return (0);

	for (i = 0; envp[i] != NULL; i++)
	{
		write(STDOUT_FILENO, envp[i], _strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (1);
}

