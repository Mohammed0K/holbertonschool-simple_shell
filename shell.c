#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
       #include <sys/wait.h>
int main(int argc, char *argv[], char *env[])
{
    char *command_argc[] = {NULL};
    size_t number_of_char;
    char *line = NULL;
    char *envp[] = {NULL};
    pid_t cpid,w;
    int    wstatus;
    while (1){
        printf("$");
        number_of_char = getline(&line, &number_of_char, stdin);
        if(number_of_char == EOF){
            return(0);
        }
        line[number_of_char - 1] = '\0';
        command_argc[0] = malloc(sizeof(char)*(number_of_char-1));
        strcpy(command_argc[0], line);
        cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code executed by child */
 if (execve(line, command_argc, envp)==-1)
        printf("%s",line);
 perror("");

           } else {                    /* Code executed by parent */
               do {
                   w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }
               } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
           }
           //printf("\n");
    }

}
