/*
** minishell.h
**
** This is the brain of the entire project - the header file that every
** single .c file will include. It is the contract between all parts
** of the program.
**
** What lives here:
**
**   1. ALL structs - the data structures that define how information
**      flows through the program. The lexer creates tokens, the parser
**      creates commands, the executor reads commands. They all need to
**      agree on what those things look like. That agreement lives here.
**
**   2. ALL enums - named constants like token types (WORD, PIPE, etc.)
**      so we never use magic numbers like 0, 1, 2 in our code.
**
**   3. ALL function prototypes - declarations of every function so that
**      any file can call any function without the compiler complaining.
**
**   4. ALL includes - we include system headers like <stdio.h> and
**      <readline/readline.h> once here, so every file gets them.
**
**   5. The global variable declaration - our one allowed global variable
**      for signal handling.
**
** Think of minishell.h as the dictionary of our project. Before two
** people can have a conversation, they need to agree on what words mean.
** This file is where we define what everything means.
**
** IMPORTANT: This file is included by everyone, so be careful what you
** put here. A mistake here breaks every single file in the project.
*/