/*
** parser.c
**
** The parser is the second stage of processing user input.
** It receives the token list from the lexer and transforms it into
** a list of command structs that the executor can understand and run.
**
** What does the parser actually do?
**   It looks at the tokens in order and groups them into commands.
**   When it sees WORD tokens, it collects them as arguments.
**   When it sees a PIPE token, it knows a new command is starting.
**   When it sees a redirection token like REDIR_OUT, it knows the
**   next WORD token is a filename, not an argument.
**
** Example:
**   Input tokens: [WORD:"ls"] [WORD:"-la"] [PIPE] [WORD:"grep"]
**                 [WORD:"foo"] [REDIR_OUT] [WORD:"out.txt"]
**
**   Output commands:
**     cmd1: args=["ls", "-la", NULL],  redirs=NULL
**     cmd2: args=["grep", "foo", NULL], redirs=[REDIR_OUT, "out.txt"]
**
** The parser does NOT:
**   - Execute anything
**   - Expand variables (that is the expanders job)
**   - Handle pipes between processes (that is the executors job)
**   - Check if commands exist on the system
**
** Think of the parser like someone reading a recipe. They dont cook
** anything yet - they just read the instructions and organize them
** into clear steps: "first do this, then do that, then do this."
*/