/*
** lexer_utils.c
**
** This file contains helper functions that support the main lexer.
** In 42 projects we split code across multiple files to keep each
** file focused and readable. lexer.c handles the main logic, and
** this file handles the smaller tasks that lexer.c needs.
**
** What kind of helpers live here:
**
**   - Functions that check what kind of character we are looking at.
**     For example: is this character a whitespace? is it a quote?
**     is it a special operator character?
**
**   - Functions that create a new token node and allocate memory for it.
**     Every time the lexer identifies a new token, it needs to create
**     a struct, fill it with data, and attach it to the linked list.
**     That process lives here.
**
**   - Functions that add a token to the end of the token linked list.
**
**   - Functions that handle reading quoted strings - when we see a
**     single or double quote, we need special logic to read everything
**     inside it as one token, even if it contains spaces.
**
** Think of this file as the toolbox that lexer.c reaches into whenever
** it needs to do a small specific task.
*/