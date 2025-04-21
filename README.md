# Simple Shell Project

## Overview

This project is an implementation of a simple Unix command interpreter (shell) written in C. The project aims to understand how a shell works and apply fundamental Unix operating system concepts such as processes, system calls, and file management.

## Historical Background

- The original Unix operating system was designed and implemented by Ken Thompson and Dennis Ritchie in 1969 while working at AT&T Bell Labs.
- Ken Thompson wrote the first version of the UNIX shell.
- Ken Thompson also invented the B programming language, which is the direct predecessor to the C programming language.

## How a Shell Works

A shell is a program that provides an interface between the user and the operating system. The shell works as follows:

1. **Display Prompt**: The shell displays a prompt and waits for user input.
2. **Read Command**: The shell reads the command entered by the user.
3. **Parse Command**: It parses the command into words and identifies the program to execute and its arguments.
4. **Search for Program**: The shell searches for the program in the paths specified in the PATH environment variable.
5. **Execute Program**: The shell creates a new process using fork() and then replaces the child process image with the requested program using execve().
6. **Wait for Completion**: The shell waits for the program to complete execution using wait() or waitpid().
7. **Repeat**: After the program completes, the shell displays the prompt again and waits for the next command.

## Requirements

### General Requirements

- Allowed editors: vi, vim, emacs
- All files will be compiled on Ubuntu 20.04 LTS using gcc with the options: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All files should end with a new line
- A README.md file at the root of the project folder is mandatory
- Code should follow the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- The shell should not have any memory leaks
- No more than 5 functions per file
- All header files should be include guarded
- Use system calls only when necessary

### Output

- The program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
- The only difference is when printing an error, the name of the program must be equivalent to argv[0].

### Allowed Functions and System Calls

- All functions from string.h
- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- printf (man 3 printf)
- fprintf (man 3 fprintf)
- vfprintf (man 3 vfprintf)
- sprintf (man 3 sprintf)
- putchar (man 3 putchar)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

## Compilation

The shell will be compiled as follows:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing

### Interactive Mode

```bash
julien@ubuntu:/# ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
julien@ubuntu:/#
```

### Non-Interactive Mode

```bash
julien@ubuntu:/# echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
julien@ubuntu:/# cat test_ls_2
/bin/ls
/bin/ls
julien@ubuntu:/# cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
julien@ubuntu:/#
```

## Tasks

### 0. README, man, AUTHORS

- Write a README
- Write a man for your shell
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository

### 1. Betty would be proud

- Write a beautiful code that passes the Betty checks

### 2. Simple shell 0.1

- Write a UNIX command line interpreter
- Display a prompt and wait for the user to type a command
- Handle simple commands with no arguments
- Handle errors and "end of file" condition (Ctrl+D)

### 3. Simple shell 0.2

- Simple shell 0.1 +
- Handle command lines with arguments

### 4. Simple shell 0.3

- Simple shell 0.2 +
- Handle the PATH
- fork must not be called if the command doesn't exist

### 5. Simple shell 0.4

- Simple shell 0.3 +
- Implement the exit built-in, that exits the shell

### 6. Simple shell 1.0

- Simple shell 0.4 +
- Implement the env built-in, that prints the current environment

## Core Concepts Used

### Processes

- **PID (Process ID)**: A unique identifier assigned by the kernel to each process.
- **PPID (Parent Process ID)**: The ID of the parent process that created the current process.
- **fork()**: A system call used to create a new process (child process) which is a copy of the original process.
- **execve()**: A system call used to execute another program, replacing the current process with a new program.
- **wait() / waitpid()**: System calls used to suspend the execution of a process until one of its child processes terminates.

### Environment

- Environment variables are stored values in the system that programs can access.
- The environment can be accessed through the third parameter to main: `char **envp` or through the global variable `environ`.
- PATH is an environment variable that contains a list of directories where the shell looks for programs.

### EOF (End of File)

- EOF is a condition that indicates the end of a file or data stream.
- In Linux, EOF can be manually entered using Ctrl+D.
- The shell uses EOF to know when to stop reading input.

## Authors

- [Author Name 1]
- [Author Name 2]

## License

This project is licensed under [License Type].

