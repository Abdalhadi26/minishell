/*
** env_init.c
**
** This file handles the initialization of our own environment copy.
** At startup, the operating system gives us the environment as envp,
** which is a char** (array of strings like "HOME=/home/student").
** We convert that into our own linked list of t_env structs.
**
** Why copy the environment?
**   The original envp array is read-only in practice and has a fixed
**   size. We need to be able to add variables (export), remove them
**   (unset), and modify them (cd updating PWD). A linked list lets
**   us do all of that freely.
**
** How we parse each envp string:
**   Each string looks like "KEY=value" or sometimes just "KEY" with no value.
**   We find the = character, split the string there, and store the
**   left part as key and the right part as value.
**   If there is no = we store the key with an empty value.
**
** What else happens at initialization:
**   We also set up SHLVL (shell level) here - if it exists we increment
**   it by 1 since we are starting a new shell. This is what lets the
**   system know how many shells are nested inside each other.
**
** Think of this file as the setup crew that arrives before the show
** starts, converting the raw environment data into the clean structure
** our shell will use throughout its entire lifetime.
*/