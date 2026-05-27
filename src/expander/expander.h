#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../includes/minishell.h"

/* Expands variables and handles quoting within strings */
char	*expand_string(char *str, t_shell shell, int flag);
char	*append_char(char *str, char c);
/* Checks whether a lexer token contains a variable to expand */
int		has_var(t_lexer *token, int flag);
char	*get_env_value(char *var_name, char **env);
/* Iterates lexer list and expands tokens in-place */
t_lexer	*expand_lexer_tokens(t_lexer *lexer, t_shell shell);
char	*handle_exit_status(char *res, t_shell shell, int *i);
char	*handle_env_var(char *res, char *str, t_shell shell, int *i);
int		handle_quotes(char c, int *sq, int *dq);
char	*handle_digit(char *res, char *str, int *i);
char	*handle_dollar(char *res, char *str, t_shell shell, int *i);
#endif

