/*
** syntax.c
**
** This file is responsible for detecting and reporting syntax errors
** in the user input before we even try to execute anything.
**
** What is a syntax error in a shell?
**   A syntax error is when the user types something that is structurally
**   wrong - not just a wrong command, but input that doesnt make sense
**   as a shell command at all.
**
** Examples of syntax errors we need to catch:
**   "ls |"       - pipe with nothing after it
**   "ls | | wc"  - two pipes in a row
**   "ls >"       - redirection with no filename after it
**   "ls >>>"     - triple redirect operator
**   unclosed quotes like:  echo "hello
**
** How it works:
**   We walk through the token list and check for illegal patterns.
**   For example: a PIPE token should never be the last token,
**   and a PIPE token should never be followed by another PIPE token.
**   A REDIR token should always be followed by a WORD token.
**
** When we find an error we print a message that matches bash:
**   "minishell: syntax error near unexpected token `|'"
**   and we set $? to 2, which is the standard exit code for syntax errors.
**
** Think of this file as the grammar checker. Before the parser tries
** to make sense of the tokens, the syntax checker makes sure the
** sentence is grammatically valid at all.
*/