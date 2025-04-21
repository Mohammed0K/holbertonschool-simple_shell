#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants */
#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"
#define PROMPT "$ "

/* Data Structures */
/**
 * struct builtin_s - Builtin command structure
 * @name: Name of the builtin command
 * @func: Function pointer to the builtin command function
 */
typedef struct builtin_s
{
	char *name;
	int (*func)(char **args, char **envp);
} builtin_t;

/* Function Prototypes */
/* main.c */
void interactive_mode(char **envp);
void non_interactive_mode(char **envp);
void process_command(char *command, char **envp);

/* execute.c */
int execute_command(char **args, char **envp);
char *find_command_path(char *command, char **envp);
void handle_execution_error(char *command, char *program_name);

/* parser.c */
char **parse_command(char *command);
void free_args(char **args);

/* builtins.c */
int is_builtin(char *command);
int execute_builtin(char **args, char **envp);
int builtin_exit(char **args, char **envp);
int builtin_env(char **args, char **envp);

/* path.c */
char *get_path_env(char **envp);
char **split_path(char *path_env);
char *build_command_path(char *directory, char *command);

/* helpers.c */
char *read_line(void);
int _strlen(char *s);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);

#endif /* SHELL_H */

