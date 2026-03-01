/*
** main.c
**
** This is the entry point of the entire minishell program.
** Everything starts and ends here.
**
** What happens here:
**   1. We receive the environment variables from the operating system
**      through the envp parameter in main() and copy them into our
**      own data structure so we can modify them freely.
**
**   2. We set up signal handlers so the shell reacts correctly to
**      ctrl-C, ctrl-D and ctrl-\ from the very start.
**
**   3. We run the main loop - this is the heartbeat of the shell:
**        - readline() waits for the user to type something and press enter
**        - we send that input through the lexer, parser, expander, executor
**        - we free the memory used by that command
**        - we loop back and wait for the next input
**
**   4. When the user exits (ctrl-D or the exit builtin), we clean up
**      all allocated memory and exit gracefully.
**
** Think of main.c as the conductor of an orchestra - it doesnt play
** any instrument itself, but it coordinates everything else.
*/