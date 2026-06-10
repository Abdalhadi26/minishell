/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:27:16 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/06 18:21:12 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "./lexer.h"
# include "./minishell.h"

typedef struct s_expander_data
{
	char	*line;
	char	*expanded;
	int		*spaces;
	t_shell	shell;
}			t_expander_data;

/*main expansion function*/
t_lexer		*expand_tokens(t_lexer *lexer, t_shell shell);

/* Function prototypes for variable expansion */
int			has_variable(t_lexer *token, int flag);
char		*get_env_value(char *var_name, char **env);
int			index_of_var(t_expander_data *data, int *i, int *j);
char		*expand_variables(char *str, t_shell shell, int flag);
int			clean_var(char **var, int i);

/*functions for handling spaces inside variables*/
int			split_after_expansion(char *expanded, t_shell shell, t_lexer **tok);
int			collect_spaces(t_expander_data *data);
t_lexer		*makesplit(char *dest, int *spaces);

char		*append_char(char *str, char c);

/* Handle different cases of variable expansion */
int			handle_quotes(char c, int *sq, int *dq);
char		*handle_exit_status(char *res, t_shell shell, int *i);
char		*handle_env_var(char *res, char *str, t_shell shell, int *i);
char		*handle_digit(char *res, char *str, int *i);
char		*handle_dollar(char *res, char *str, t_shell shell, int *i);
#endif