/*
** lexer.c
**
** The lexer is the first stage of processing user input.
** Its job is to take the raw string the user typed and break it
** into a list of tokens - meaningful pieces that the parser can work with.
**
** What is a token?
**   A token is the smallest meaningful unit of input. Just like how
**   a sentence in English is made of words and punctuation, a shell
**   command is made of words, pipes, and redirections. Each one is a token.
**
** Example:
**   Input:  "ls -la | grep foo > out.txt"
**   Output: [WORD:"ls"] [WORD:"-la"] [PIPE] [WORD:"grep"]
**           [WORD:"foo"] [REDIR_OUT] [WORD:"out.txt"]
**
** How it works:
**   The lexer reads the input string one character at a time.
**   When it sees a special character like | or > or <, it creates
**   a token for that operator.
**   When it sees a quote, it reads everything inside as one word.
**   When it sees regular characters, it reads until a space or
**   special character and creates a WORD token.
**
** What the lexer does NOT do:
**   - It does not understand what the tokens mean together
**   - It does not expand $VARIABLES
**   - It does not check if the syntax is valid
**   - It does not care what ls or grep are
**
** Think of the lexer like a scanner that reads a document and
** highlights every word and punctuation mark individually, without
** understanding what the document says.
*/