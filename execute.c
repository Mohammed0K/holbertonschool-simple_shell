#include "shell.h"

/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * @envp: Environment variables
 * @program_name: Name of the program
 *
 * Return: Exit status of the command
 */
int execute_command(char **args, char **envp, char *program_name)
{
	pid_t pid;
	int status = 0;
	char *command_path;

	if (args == NULL || args[0] == NULL)
		return (0);

	/* Handle built-in "exit" command before forking */
	if (_strcmp(args[0], "exit") == 0)
	{
		int exit_status = 0;

		if (args[1])
			exit_status = _atoi(args[1]);

		free_args(args); /* Ensure memory is freed */
		exit(exit_status); /* Clean exit */
	}

	command_path = find_command_path(args[0], envp);
	if (command_path == NULL)
	{
		handle_execution_error(args[0], program_name);
		return (127); /* Command not found */
	}

	/* Only fork if command exists */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		return (1);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(command_path, args, envp) == -1)
		{
			handle_execution_error(args[0], program_name);
			free(command_path);
			exit(127); /* Command not found */
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
		free(command_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (status);
}

/**
 * find_command_path - Find the full path of a command
 * @command: Command to find
 * @envp: Environment variables
 *
 * Return: Full path of the command, or NULL if not found
 */
char *find_command_path(char *command, char **envp)
{
	char *path_env, **path_dirs, *command_path;
	int i;
	struct stat st;

	if (command == NULL)
		return (NULL);

	/* Check if command is an absolute or relative path */
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (_strdup(command));
		return (NULL);
	}

	path_env = get_path_env(envp);
	if (path_env == NULL || path_env[0] == '\0')
	{
		free(path_env);
		return (NULL);
	}

	path_dirs = split_path(path_env);
	if (path_dirs == NULL)
	{
		free(path_env);
		return (NULL);
	}

	for (i = 0; path_dirs[i] != NULL; i++)
	{
		command_path = build_command_path(path_dirs[i], command);
		if (command_path == NULL)
			continue;

		if (stat(command_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_env);
			free_args(path_dirs);
			return (command_path);
		}
		free(command_path);
	}

	free(path_env);
	free_args(path_dirs);
	return (NULL);
}

/**
 * handle_execution_error - Handle execution errors
 * @command: Command that failed
 * @program_name: Name of the program
 *
 * Return: void
 */
void handle_execution_error(char *command, char *program_name)
{
	char error_message[BUFFER_SIZE];
	int len;

	len = snprintf(error_message, BUFFER_SIZE, "%s: 1: %s: not found\n",
		       program_name, command);
	write(STDERR_FILENO, error_message, len);
}
