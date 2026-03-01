/*
** env.c
**
** Implements the env builtin.
** env prints all current environment variables to standard output.
**
** This is one of the simpler builtins.
** We walk our environment linked list from start to finish and
** print each variable in the format: KEY=value
** Each variable is on its own line.
**
** The difference between env and export with no arguments:
**   env prints:    KEY=value
**   export prints: declare -x KEY="value"
**   They show the same information but in different formats.
**
** Why does our own environment copy matter here?
**   If we just printed the original envp from main(), we would
**   never see variables added with export or removed with unset.
**   Because we maintain our own linked list and modify that list
**   when export and unset run, env always shows the current state.
**
** Think of env as a window that lets you see the entire contents
** of the shells environment dictionary at any moment.
*/