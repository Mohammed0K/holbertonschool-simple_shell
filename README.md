# Simple Shell Project

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](./)
[![Coverage](https://img.shields.io/badge/coverage-100%25-yellow)](./)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)

## Table of Contents

- [Description](#description)  
- [Installation](#installation)  
- [Usage](#usage)  
- [Configuration](#configuration)  
- [Examples](#examples)  
- [API Reference](#api-reference)  
- [Contributing](#contributing)  
- [Contact / Support](#contact--support)  

## Description

**Simple Shell** is a basic UNIX command interpreter written in C.  
It demonstrates core OS concepts such as process creation, system calls,  
and environment management. Features include:

- Interactive and non‑interactive modes  
- Execution of external commands via `fork()` and `execve()`  
- Built‑in commands: `exit`, `env`  
- PATH resolution for locating executables  
- Error handling consistent with `/bin/sh`  

## Installation

1. Clone the repository:  
   ```bash
   git clone https://github.com/yourusername/holbertonschool-simple_shell.git
   cd holbertonschool-simple_shell
   ```
2. Compile the shell:  
   ```bash
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

## Usage

### Interactive Mode

Start the shell and enter commands at the prompt:

```bash
$ ./hsh
$ /bin/ls
file1.c  file2.c  README.md
$ exit
```

### Non‑Interactive Mode

Feed commands via a pipe or file:

```bash
echo "/bin/ls" | ./hsh
file1.c  file2.c  README.md
```

## Configuration

- **PATH**: The shell reads the `PATH` environment variable to locate  
  executables.
- **Prompt**: Defined by `PROMPT` in `shell.h` (default: `"$ "`).  
- No additional configuration files are required.

## Examples

![Interactive Shell Example](./images/interactive_example.png)

```bash
$ ./hsh
$ env
HOME=/home/user
PATH=/usr/local/bin:/usr/bin:/bin
$ exit
```

## API Reference

The following functions are exposed via `shell.h`:

- **`int main(int, char**, char**)`** — Entry point; dispatches modes.  
- **`void interactive_mode(char**, char*, int*)`** — Read‑eval loop in tty.  
- **`void non_interactive_mode(char**, char*, int*)`** — Process piped input.  
- **`int process_command(char*, char**, char*)`** — Parse & dispatch commands.  
- **`char **parse_command(char*)`** — Tokenize a command line.  
- **`int execute_command(char**, char**, char*)`** — Fork & exec external cmd.  
- **`int is_builtin(char*)`** — Detect built‑in commands.  
- **`int execute_builtin(char**, char**)`** — Invoke built‑in handler.  
- **`char *find_command_path(char*, char**)`** — Resolve full path.  
- **`char *get_path_env(char**)`** — Extract `PATH` value.  
- **`char **split_path(char*)`** — Split `PATH` into directories.  
- **`char *build_command_path(char*, char*)`** — Construct full cmd path.  
- **Utility functions** (`_strlen`, `_strdup`, `_strcmp`, `_atoi`, etc.)

## Contributing

Please follow these guidelines when contributing:

1. Fork the repository and create a feature branch.  
2. Adhere to [Betty coding style](https://github.com/alx-tools/Betty/wiki).  
3. Write meaningful commit messages prefixed with `feat:`, `fix:`, `docs:`,  
   or `chore:`.  
4. Include tests or manual QA steps for new functionality.  
5. Submit a pull request against `main`, describing your changes.


## Contact / Support

- File issues via the [GitHub issues page](https://github.com/yourusername/holbertonschool-simple_shell/issues).  
- For questions or feedback, email the maintainers:  
  - Bader Alamri <bader.alamri@holbertonstudents.com>  
  - Hamad Dahash <hamad.dahash@holbertonstudents.com>  
  - Mohammed Alqabas <mohammed.alqabas@holbertonstudents.com>  
