/*
** echo.c
**
** Implements the echo builtin command.
** echo prints its arguments to standard output.
**
** Why is echo a builtin?
**   Because the subject requires it. In real bash, echo is both
**   a builtin AND an external program (/bin/echo). We only need
**   to implement the builtin version.
**
** The -n flag:
**   By default echo prints a newline at the end of its output.
**   The -n flag suppresses that newline.
**   Example: echo hello      prints: hello\n
**   Example: echo -n hello   prints: hello  (no newline, prompt follows)
**
** The tricky part about -n:
**   Multiple -n flags are all valid: echo -n -n -n hello
**   A flag like -nnn is also valid (all n's after the dash)
**   But -nnnb is NOT a valid -n flag (contains a non-n character)
**   So echo -nnnb hello  prints: -nnnb hello  (with newline)
**   The rule: strip leading -n flags as long as every character
**   after the dash is the letter n. Stop at the first non-n character.
**
** Think of echo as the simplest possible builtin - it just prints
** what you give it. The complexity is entirely in the -n flag logic.
*/