*This project has been created as part of the 42 curriculum by mohassaf, hammeah.*

# Minishell

## Description

Minishell is a small Unix shell written in C. The goal of the project is to reproduce core behavior of a real shell while learning about processes, file descriptors, parsing, signals, environment variables, and command execution.

The program reads a command line, parses it into commands and redirections, expands variables, then executes builtins or external programs using pipes, forks, and redirections.

Project responsibilities:

- Parsing was implemented by my teammate.
- Execution was implemented by me.

## Features

- Interactive prompt using `readline`
- Command parsing and tokenization
- Environment variable expansion, including `$?`
- Builtin commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- External command execution through `PATH`
- Pipes with `|`
- Redirections:
  - input: `<`
  - output: `>`
  - append: `>>`
  - heredoc: `<<`
- Signal handling for interactive and execution modes

## Instructions

### Compilation

From the repository root, run:

```sh
make
```

This creates the executable:

```sh
./minishell
```

### Cleaning

Remove object files:

```sh
make clean
```

Remove object files and the executable:

```sh
make fclean
```

Rebuild from scratch:

```sh
make re
```

## Usage Examples

Start the shell:

```sh
./minishell
```

Run simple commands:

```sh
minishell$ pwd
minishell$ echo hello world
minishell$ ls -la
```

Use pipes and redirections:

```sh
minishell$ ls | grep .c
minishell$ echo hello > file.txt
minishell$ cat < file.txt
minishell$ cat << EOF
```

Use environment variables:

```sh
minishell$ echo $PATH
minishell$ echo $?
minishell$ export NAME=minishell
minishell$ echo $NAME
```

## Project Structure

- `builtin/`: builtin shell commands
- `exec/`: command path lookup, process handling, and execution helpers
- `parsing/`: tokenization, parsing, environment copying, and expansion
- `redir/`: pipes, heredoc handling, and redirections
- `utils/`: cleanup, printing, and signal handling
- `header/`: shared project header
- `libft/`: custom C utility library used by the project
- `src/`: program entry point

## Resources

Classic references used for this project:

- GNU Bash manual: https://www.gnu.org/software/bash/manual/
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- Linux manual pages: https://man7.org/linux/man-pages/
- `fork(2)`: https://man7.org/linux/man-pages/man2/fork.2.html
- `execve(2)`: https://man7.org/linux/man-pages/man2/execve.2.html
- `pipe(2)`: https://man7.org/linux/man-pages/man2/pipe.2.html
- `dup2(2)`: https://man7.org/linux/man-pages/man2/dup.2.html
- `waitpid(2)`: https://man7.org/linux/man-pages/man2/waitpid.2.html
- GNU Readline documentation: https://tiswww.case.edu/php/chet/readline/readline.html

AI usage:

AI was used as a support tool to help review compiler errors, improve documentation wording, and clarify how to describe the project structure and responsibilities in the README. The implementation itself remains the responsibility of the project authors. In particular, the parsing part was handled by my teammate, and the execution part was handled by me.
