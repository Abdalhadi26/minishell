*This project has been created as part of the 42 curriculum by aayasrah, ahhammad.*

# minishell

## Description

`minishell` is a minimal Unix shell written in C that recreates the core
behaviour of `bash` in interactive mode. The goal of the project is to
understand how a shell works: reading a line, parsing it into commands and
redirections, expanding variables, and executing programs through
`fork`/`execve` while managing pipes, file descriptors, signals, and memory.

It displays a prompt, keeps a command history, and supports pipelines,
redirections, here-documents, environment-variable expansion, quoting, a set
of built-in commands, and interactive signal handling.

### Features

- Command execution via `PATH` lookup, plus absolute and relative paths.
- Pipes (`|`) of arbitrary length.
- Redirections: `<` (input), `>` (truncate), `>>` (append), `<<` (here-doc).
- Environment variable expansion: `$VAR` and `$?` (last exit status).
- Single `'` and double `"` quoting (expansion disabled inside single quotes).
- Signals: `Ctrl-C`, `Ctrl-D`, `Ctrl-\`, including aborting a here-doc with `Ctrl-C`.
- Built-ins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Instructions

### Requirements

- `cc`, `make`
- GNU `readline` development library
  - Debian/Ubuntu: `sudo apt install libreadline-dev`
  - macOS (Homebrew): `brew install readline`

### Compilation

```bash
make        # build the minishell binary
make clean  # remove object files
make fclean # remove objects and the binary
make re     # rebuild from scratch
```

### Execution

```bash
./minishell
```

Example session:

```
minishell$ echo hello | cat -e
hello$
minishell$ ls -la > out.txt
minishell$ cat << EOF
> line one
> EOF
line one
minishell$ exit
```

## Resources

Classic references used while working on the project:

- *The Linux Programming Interface*, Michael Kerrisk — processes, pipes, signals.
- GNU `readline` documentation — https://tiswww.case.edu/php/chet/readline/readline.html
- `man` pages: `bash(1)`, `execve(2)`, `fork(2)`, `pipe(2)`, `dup2(2)`,
  `wait(2)`, `signal(2)`, `sigaction(2)`, `open(2)`.
- The `bash` reference manual — https://www.gnu.org/software/bash/manual/

### Use of AI

AI was used occasionally as a debugging aid — mainly to help track down a
file-descriptor leak and to reason about `valgrind` output. All suggestions
were reviewed and tested by the authors before being integrated.
