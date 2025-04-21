uu#include "shell.h"

/**
 * get_path_env - Get value of PATH environment variable
 * @envp: Environment variables
 *
 * Return: Value of PATH environment variable, or NULL if not found
 */
char *get_path_env(char **envp)
{
	int i;
	char *path_env = NULL;
	char *path_prefix = "PATH=";
	int prefix_len = 5;

	if (envp == NULL)
		return (_strdup(""));

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], path_prefix, prefix_len) == 0)
		{
			path_env = _strdup(envp[i] + prefix_len);
			return (path_env);
		}
	}

	/* Return empty string if PATH is not found */
	return (_strdup(""));
}

/**
 * split_path - Split PATH into array of directories
 * @path_env: PATH environment variable value
 *
 * Return: Array of directories
 */
char **split_path(char *path_env)
{
	char **path_dirs;
	char *token;
	int i = 0;
	int buffer_size = BUFFER_SIZE;

	if (path_env == NULL)
		return (NULL);

	/* If PATH is empty, return empty array */
	if (path_env[0] == '\0')
	{
		path_dirs = malloc(sizeof(char *));
		if (path_dirs == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		path_dirs[0] = NULL;
		return (path_dirs);
	}

	path_dirs = malloc(buffer_size * sizeof(char *));
	if (path_dirs == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(path_env, ":");
	while (token != NULL)
	{
		path_dirs[i] = _strdup(token);
		if (path_dirs[i] == NULL)
		{
			perror("strdup");
			free_args(path_dirs);
			return (NULL);
		}
		i++;

		if (i >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			path_dirs = realloc(path_dirs, buffer_size * sizeof(char *));
			if (path_dirs == NULL)
			{
				perror("realloc");
				return (NULL);
			}
		}

		token = strtok(NULL, ":");
	}
	path_dirs[i] = NULL;

	return (path_dirs);
}

/**
 * build_command_path - Build full path to command
 * @directory: Directory to check
 * @command: Command to find
 *
 * Return: Full path to command, or NULL on failure
 */
char *build_command_path(char *directory, char *command)
{
	char *command_path;
	int dir_len, cmd_len;

	if (directory == NULL || command == NULL)
		return (NULL);

	dir_len = _strlen(directory);
	cmd_len = _strlen(command);

	command_path = malloc(dir_len + cmd_len + 2);
	if (command_path == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	strcpy(command_path, directory);
	command_path[dir_len] = '/';
	strcpy(command_path + dir_len + 1, command);

	return (command_path);
}

