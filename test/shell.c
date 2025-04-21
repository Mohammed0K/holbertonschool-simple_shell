#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char *find_command(char *command)
{
char *path_env = NULL;
char *path_copy, *dir;
char full_path[1024];
int i = 0;

/* search PATH manually inside environ */

while (environ[i])
{
if (strncmp(environ[i], "PATH=", 5) == 0)
{
path_env = environ[i] + 5;
break;
}
i++;
}

if (!path_env)
return (NULL);

path_copy = strdup(path_env);
dir = strtok(path_copy, ":");

while (dir)
{
sprintf(full_path, "%s/%s", dir, command);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (strdup(full_path));
}
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}

char *resolve_cmd_path(char *cmd)
{
char *cmd_path = NULL;

if (strchr(cmd, '/'))
{
if (access(cmd, X_OK) == 0)
cmd_path = strdup(cmd);
}
else
cmd_path = find_command(cmd);

return (cmd_path);
}

void tokenize(char *command, char **command_args)
{
	int i = 0;
	
	command_args[0] = strtok(command, " ");
	while (command_args[i])
	{
		i++;
		command_args[i] = strtok(NULL, " ");
	}
}
void free_command_args(char **command_args)
{
	free(command_args);
}
int main(void)
{
	char *cmd_path, **command_args;
	size_t number_of_char;
	char *line = NULL;
	char *envp[] = {NULL};
	pid_t cpid, w;
	int wstatus;

	command_args = malloc(sizeof(char *) * 10);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$");
		number_of_char = getline(&line, &number_of_char, stdin);
		if ((int)number_of_char == EOF)
			break;
		line[number_of_char - 1] = '\0';
		tokenize(line, command_args);
		cmd_path = resolve_cmd_path(command_args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", command_args[0]);
			free_command_args(command_args);
			return (127);
		}
		cpid = fork();
		if (cpid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (cpid == 0)
		{
			if (command_args[0] && execve(cmd_path, command_args, envp) == -1)
				perror("./hsh");
		}
		else
		{
			do {
				w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
				if (w == -1)
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		}
	}
	free(line);
	free_command_args(command_args);
	return (0);
}
