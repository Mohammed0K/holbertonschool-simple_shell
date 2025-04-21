#include "shell.h"

/**
 * parse_command - Parse a command line into an array of arguments
 * @command: Command line to parse
 *
 * Return: Array of arguments
 */
char **parse_command(char *command)
{
	char **args;
	char *token;
	int i = 0;
	int buffer_size = BUFFER_SIZE;

	if (command == NULL)
		return (NULL);

	args = malloc(buffer_size * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(command, TOKEN_DELIM);
	while (token != NULL)
	{
		args[i] = _strdup(token);
		if (args[i] == NULL)
		{
			perror("strdup");
			free_args(args);
			return (NULL);
		}
		i++;

		if (i >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			args = realloc(args, buffer_size * sizeof(char *));
			if (args == NULL)
			{
				perror("realloc");
				return (NULL);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	args[i] = NULL;

	return (args);
}

/**
 * free_args - Free memory allocated for argument array
 * @args: Array of arguments
 *
 * Return: void
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
}

