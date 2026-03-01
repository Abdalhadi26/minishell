/*
** pipes.c
**
** This file handles the creation and management of Unix pipes.
** A pipe is a communication channel between two processes - one
** process writes into one end, another reads from the other end.
**
** What is a pipe in Unix?
**   When you run ls | grep foo, you want the OUTPUT of ls to become
**   the INPUT of grep. A pipe is how the operating system connects them.
**   The pipe() system call creates two file descriptors:
**     fd[0] - the read end  (grep reads from here)
**     fd[1] - the write end (ls writes to here)
**
** The most important and most commonly misunderstood rule about pipes:
**   You MUST close every pipe end that you dont use.
**   If the parent forgets to close the write end of a pipe, the child
**   reading from that pipe will NEVER receive EOF and will hang forever,
**   waiting for input that will never come. This is the most common bug
**   in minishell implementations.
**
** What this file handles:
**   - Creating the right number of pipes for a pipeline
**     (N commands need N-1 pipes)
**   - Connecting pipe ends to stdin and stdout using dup2()
**   - Closing all pipe ends that are no longer needed
**   - Making sure no file descriptors are leaked to child processes
**
** Think of pipes like a physical tube between two people. If you dont
** cap (close) the ends you are not using, air (data) leaks everywhere
** and nothing works correctly.
*/