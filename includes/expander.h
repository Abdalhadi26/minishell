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

typedef struct s_data
{
	char	*input;
	char	*expanded;
	int		*spaces;
	t_shell	shell;
	int		index[2];
}			t_data;

char		*append_char(char *str, char c);
int			has_var(t_lexer *token, int flag);
char		*get_env_value(char *var_name, char **env);
t_lexer		*expand_lexer_tokens(t_lexer *lexer, t_shell shell);
char		*handle_exit_status(char *res, t_shell shell, int *i);
char		*handle_env_var(char *res, char *str, t_shell shell, int *i);
char		*handle_digit(char *res, char *str, int *i);
char		*handle_dollar(char *res, char *str, t_shell shell, int *i);
int			main_expander(char *expanded, t_shell shell, t_lexer **tok);
int			handle_quotes(char c, int *sq, int *dq);
int			lol(t_data *data);
int			main_expander(char *expanded, t_shell shell, t_lexer **tok);
int			free_var(char **var, int i);
t_lexer		*makesplit(char *dest, int *spaces);
int			index_of_var(t_data *data, int *i, int *j);
char		*expand_string(char *str, t_shell shell, int flag);
#endif