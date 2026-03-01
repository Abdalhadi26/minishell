/*
** env_utils.c
**
** This file contains all the utility functions for interacting with
** our environment linked list throughout the program.
**
** The four fundamental operations on our environment:
**
**   GET - find the value of a variable by name
**     We walk the linked list comparing keys until we find a match.
**     Returns the value string or NULL if not found.
**     Used constantly by the expander when it sees $VARNAME.
**
**   SET - add or update a variable
**     First check if the variable already exists.
**     If yes, update its value.
**     If no, create a new node and add it to the list.
**     Used by export and by cd when updating PWD.
**
**   DELETE - remove a variable by name
**     Find the node, unlink it from the list, free its memory.
**     Used by unset.
**
**   TO_ARRAY - convert the linked list back to char**
**     execve() needs the environment as a char** array, not a linked list.
**     We count the nodes, malloc an array, fill it with "KEY=value" strings.
**     Used by the executor every time it calls execve().
**
** Think of this file as the complete API for our environment database -
** every part of the shell that needs to read or write environment
** variables goes through the functions in this file.
*/