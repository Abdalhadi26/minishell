/*
** pwd.c
**
** Implements the pwd (print working directory) builtin.
** pwd prints the absolute path of the current directory.
**
** This is the simplest builtin in the project.
** It calls getcwd() which asks the operating system for the
** current working directory and returns it as a string.
** Then we print that string followed by a newline.
**
** Why is pwd a builtin?
**   Technically pwd could be an external program and it would work
**   fine - unlike cd, it doesnt need to modify the shell's state.
**   But the subject requires it as a builtin, so we implement it here.
**
** One subtle thing:
**   We use getcwd() rather than just reading the PWD environment variable.
**   This is more reliable because PWD might be out of date in edge cases.
**   getcwd() always asks the OS for the real current directory.
**
** Think of pwd as the shell looking down at its feet and telling you
** exactly where it is standing in the filesystem.
*/