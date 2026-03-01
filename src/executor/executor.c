/*
** executor.c
**
** The executor is the final and most complex stage. It receives the
** fully parsed and expanded command list and actually runs everything.
**
** This is where the real Unix system programming happens.
**
** What the executor does:
**
**   For a single command (no pipes):
**     1. Check if it is a builtin (echo, cd, pwd, etc.)
**        If yes, run it directly in the current process
**        If no, fork a child process and use execve() to run it
**
**   For a pipeline (multiple commands connected by |):
**     1. Create pipes between each pair of adjacent commands
**     2. Fork a child process for each command
**     3. In each child, connect the right pipe ends to stdin/stdout
**     4. Close all pipe ends that the child doesnt need
**     5. Execute the command with execve()
**     6. In the parent, close all pipe ends and wait for all children
**
** Key concepts used here:
**   fork()   - creates a copy of the current process
**   execve() - replaces the current process with a new program
**   wait()   - parent waits for child to finish and gets exit status
**
** Think of the executor as a manager who receives a list of tasks,
** hires workers (child processes) to do each task, sets up the
** communication channels between them (pipes), and waits for
** everyone to finish before reporting back.
*/