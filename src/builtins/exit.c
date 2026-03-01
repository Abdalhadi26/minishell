/*
** exit.c
**
** Implements the exit builtin.
** exit terminates the shell, optionally with a specific exit code.
**
** Usage:
**   exit        exits with the last commands exit status
**   exit 42     exits with code 42
**   exit -1     exits with code 255 (wraps around like bash)
**
** The exit code math:
**   Exit codes in Unix are stored as unsigned 8-bit values (0-255).
**   Any value you give is taken modulo 256.
**   So exit 256 exits with 0, exit 257 exits with 1, exit -1 exits with 255.
**
** Error cases to handle carefully:
**   exit abc        <- not a number, print error, exit with code 2
**   exit 1 2        <- too many arguments, print error, do NOT exit
**   exit 99999999999999999 <- overflow, print error, exit with code 2
**   The overflow check is important - use long long and check bounds.
**
** Why must exit be a builtin?
**   Because it needs to terminate the shell process itself. If it
**   ran in a child process, only the child would exit and the shell
**   would keep running unchanged.
**
** Important cleanup:
**   Before exiting, free ALL allocated memory - env list, any remaining
**   command structs, everything. Valgrind will check this.
**
** Think of exit as the off switch for the shell, with some careful
** math to handle the exit code correctly.
*/