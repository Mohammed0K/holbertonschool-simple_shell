#include "shell.h"

/**
 * execute_command - execute a command by forking and execve
 * @args: array of argument strings
 * @envp: array of environment variable strings
 * @program_name: name of the shell executable
 *
 * Return: exit status of the command
 */
int execute_command(char **args, char **envp, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path;

	if (args == NULL || args[0] == NULL)
	{
		return (0);
	}

	/* handle built-in exit before forking */
	if (_strcmp(args[0], "exit") == 0)
	{
		int exit_status = 0;

		if (args[1] != NULL)
		{
			exit_status = _atoi(args[1]);
		}
		free_args(args);
		exit(exit_status);
	}

	command_path = find_command_path(args[0], envp);
	if (command_path == NULL)
	{
		handle_execution_error(args[0], program_name);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		return (1);
	}
	else if (pid == 0)
	{
		/* child process */
		if (execve(command_path, args, envp) == -1)
		{
			handle_execution_error(args[0], program_name);
			free(command_path);
			exit(127);
		}
	}
	else
	{
		/* parent process */
		waitpid(pid, &status, 0);
		free(command_path);
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
	}

	return (status);
}

/**
 * find_command_path - find the full path of a command
 * @command: command to locate
 * @envp: array of environment variable strings
 *
 * Return: allocated string of command path, or NULL if not found
 */
char *find_command_path(char *command, char **envp)
{
	char *path_env, **path_dirs, *command_path;
	int i;
	struct stat st;

	if (command == NULL)
	{
		return (NULL);
	}

	/* check for absolute or relative path */
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			return (_strdup(command));
		}
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
		{
			continue;
		}
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
 * handle_execution_error - print error message for failed command
 * @command: command that failed
 * @program_name: name of the shell executable
 *
 * Return: void
 */
void handle_execution_error(char *command, char *program_name)
{
	char error_message[BUFFER_SIZE];
	int len;

	len = snprintf(error_message, BUFFER_SIZE,
		       "%s: 1: %s: not found\n",
		       program_name, command);
	write(STDERR_FILENO, error_message, len);
}
