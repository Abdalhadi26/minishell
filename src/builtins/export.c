/*
** export.c
**
** Implements the export builtin.
** export adds new variables to the environment or updates existing ones.
**
** Two ways to use export:
**
**   export VARNAME=value
**     Adds VARNAME to the environment with the given value.
**     If VARNAME already exists, its value is updated.
**     Example: export MY_NAME=student
**
**   export with no arguments
**     Prints all currently exported environment variables in a format
**     that matches bash: declare -x VARNAME="value"
**
** Validation rules:
**   Variable names must be valid identifiers.
**   A valid identifier starts with a letter or underscore,
**   followed by any combination of letters, digits, and underscores.
**   export 1test  <- INVALID, starts with a digit
**   export _test  <- valid
**   export test1  <- valid
**   When an invalid name is given, print an error but continue
**   processing the remaining arguments.
**
** Why must export be a builtin?
**   Same reason as cd - it needs to modify the shells own environment.
**   If it ran in a child process, the changes would disappear when
**   the child exited and the shell would be unchanged.
**
** Think of export as the builtin that writes new entries into the
** shells environment dictionary.
*/