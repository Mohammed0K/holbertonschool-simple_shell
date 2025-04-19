#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	char **command_args;
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
		cpid = fork();
		if (cpid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (cpid == 0)
		{
			if (command_args[0] && execve(command_args[0], command_args, envp) == -1)
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
