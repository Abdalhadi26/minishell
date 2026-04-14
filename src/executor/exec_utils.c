/*
** exec_utils.c
**
** This file contains utility functions that support the executor.
** Specifically it handles finding and launching external programs.
**
** The two main jobs here:
**
**   1. PATH searching - finding where a program actually lives
**      When you type ls, the shell doesnt know where ls is.
**      It has to search through all the directories listed in the
**      PATH environment variable to find it.
**      PATH might look like: /usr/local/bin:/usr/bin:/bin
**      We split it by : and check each directory:
**        does /usr/local/bin/ls exist? no
**        does /usr/bin/ls exist? no
**        does /bin/ls exist? YES - use this path
**      If the command already contains a / (like ./myprog or /bin/ls)
**      we skip the PATH search and use it directly.
**
**   2. execve() wrapper - actually launching the program
**      execve() completely replaces the current process with the new
**      program. It needs three things:
**        - the full path to the executable
**        - the argument array (argv)
**        - the environment array (envp)
**      We need to convert our environment linked list back into a
**      char** array because that is what execve() expects.
**      If execve() returns, it means it failed - we print an error.
**
** Think of this file as the part of the shell that knows how to
** find and launch any program on the system.
*/

#include "../../includes/minishell.h"

void	free_2d(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}