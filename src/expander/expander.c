/*
** expander.c
**
** The expander is the third stage of processing. After the parser has
** organized tokens into command structs, the expander goes through
** every argument and replaces variable references with their actual values.
**
** What does expansion mean?
**   When the user types echo $HOME, they dont literally want the string
**   "$HOME" printed. They want the VALUE of the HOME variable printed,
**   which might be "/home/student". The expander does that replacement.
**
** What gets expanded:
**   $VARNAME  - replaced with the value of that environment variable
**   $?        - replaced with the exit status of the last command
**   $0        - replaced with the name of the shell ("minishell")
**
** What does NOT get expanded:
**   Variables inside single quotes: echo '$HOME' prints literally $HOME
**   Non-existent variables: echo $NOTHING prints an empty string
**
** The expansion process:
**   We scan each argument character by character looking for $.
**   When we find $, we read the variable name that follows it.
**   We look up that name in our environment linked list.
**   We replace the $VARNAME with its value (or empty string if not found).
**
** Think of the expander like a find-and-replace tool in a text editor,
** but smarter - it knows about quotes and special cases.
*/