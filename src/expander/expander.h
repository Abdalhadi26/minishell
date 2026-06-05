/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:27:16 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/05 22:51:51 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../includes/minishell.h"
# include "../lexer/lexer.h"

typedef struct s_data //a linked list of all the redirections
{
	char	*input; //name of the files which will be redirected to
	char	*expanded;
	int		*spaces;
	t_shell	shell;
	int		index[2];
}		t_data;

/* Expands variables and handles quoting within strings */
// char	*expand_string(char *str, t_shell shell, int flag);
// t_lexer	*expand_lexer_tokens(t_lexer *lexer, t_shell shell)
char	*append_char(char *str, char c);
/* Checks whether a lexer token contains a variable to expand */
int		has_var(t_lexer *token, int flag);
char	*get_env_value(char *var_name, char **env);
/* Iterates lexer list and expands tokens in-place */
t_lexer	*expand_lexer_tokens(t_lexer *lexer, t_shell shell);
char	*handle_exit_status(char *res, t_shell shell, int *i);
char	*handle_env_var(char *res, char *str, t_shell shell, int *i);
// int	handle_quotes(t_lexer **res, char *input, int *i, t_shell shell);
char	*handle_digit(char *res, char *str, int *i);
char	*handle_dollar(char *res, char *str, t_shell shell, int *i);
int		main_expander(char *expanded, t_shell shell, t_lexer **tok);
int		handle_quotes(char c, int *sq, int *dq);
int		lol(t_data *data);
int		main_expander(char *expanded, t_shell shell, t_lexer **tok);
int		free_var(char **var, int i);
t_lexer	*makesplit(char *dest, int *spaces);
int		index_of_var(t_data *data, int *i, int *j);

char	*expand_string(char *str, t_shell shell, int flag);
#endif