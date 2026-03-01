/*
** cd.c
**
** Implements the cd (change directory) builtin.
** cd changes the current working directory of the shell.
**
** Why MUST cd be a builtin and not an external program?
**   This is a fundamental Unix concept worth understanding deeply.
**   Every process has its own current directory. If cd were an
**   external program, it would fork a child process, change the
**   directory in THAT child process, and then the child would exit.
**   The parent shell process would be completely unaffected.
**   cd MUST run inside the shell process itself to actually change
**   the shells working directory. This is true of all builtins that
**   need to affect the shells own state.
**
** What cd does:
**   1. Calls chdir() to actually change the directory
**   2. Updates the PWD environment variable to the new directory
**   3. Updates the OLDPWD environment variable to the previous directory
**      (this is what lets you do cd - to go back)
**
** Error cases to handle:
**   cd with no path: go to $HOME
**   cd with too many arguments: error message, exit status 1
**   cd to a non-existent directory: error message, exit status 1
**   cd to a directory without permission: error message, exit status 1
**
** Think of cd as the builtin that moves the shell itself around
** the filesystem, rather than running a separate program to do it.
*/