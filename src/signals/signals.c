/*
** signals.c
**
** This file handles Unix signals - asynchronous notifications that
** the operating system sends to our process when certain events happen.
**
** What is a signal?
**   A signal is like a tap on the shoulder from the OS. When you press
**   ctrl-C, the terminal sends SIGINT (signal 2) to your process.
**   When you press ctrl-\, it sends SIGQUIT (signal 3).
**   By default these signals would kill your program. We override
**   that default behavior with our own handlers.
**
** The three signals we care about:
**
**   SIGINT (ctrl-C, signal 2)
**     Interactive mode (waiting for input): show a new prompt on new line
**     While a child is running: let the child die, parent waits
**     During heredoc: cancel the heredoc, show new prompt
**
**   SIGQUIT (ctrl-\, signal 3)
**     Interactive mode: do nothing at all
**     While a child is running: child gets killed and shows "Quit (core dumped)"
**
**   SIGEOF (ctrl-D)
**     This is not actually a signal - readline() returns NULL when it
**     sees ctrl-D. We handle it in the main loop, not here.
**
** How signals interact with our global variable:
**   Our signal handler is intentionally minimal - it only stores the
**   signal number in g_signal. The main loop checks g_signal after
**   readline() returns and reacts to it there. This is safe because
**   we never access complex data structures from inside a signal handler.
**
** Think of this file as the shells nervous system - it feels the
** outside world tapping on it and decides how to react.
*/