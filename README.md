# Simple Shell

A simple UNIX command interpreter built from scratch as part of Holberton School curriculum.

## Overview

This shell provides basic command execution capabilities with support for both interactive and non-interactive modes. It's designed to help understand how shells work under the hood.

## Features

- **Interactive Mode**: Command prompt with user input
- **Non-interactive Mode**: Script execution from input stream
- **Command Arguments**: Full argument support for commands
- **PATH Resolution**: Automatic executable discovery
- **Built-in Commands**: 
  - `exit` - Exit the shell
  - `env` - Display environment variables
- **Error Handling**: Clear error messages and proper status codes

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode
```bash
./hsh
$ ls
$ /bin/ls
$ exit
```

### Non-interactive Mode
```bash
echo "ls" | ./hsh
```

## Project Structure

- `simple_shell_main.c` - Main shell program
- `main.h` - Header file with function prototypes
- `fill_argv.c` - Command parsing functionality
- `print_env.c` - Environment printing
- `getenv.c` - Environment variable handling
- `exec_exists_cmd.c` - Command execution
- `shell_errors.c` - Error handling

## Author

**Safar Gasimov**

## Requirements

- Ubuntu 20.04 LTS
- GCC compiler
- Betty style compliance

## Learning Outcomes

This project demonstrates:
- Process creation and management
- System calls (fork, execve, wait)
- Environment variable handling
- Command line parsing
- Error handling and memory management

Built as part of Holberton School curriculum.