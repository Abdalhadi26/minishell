/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:13:14 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/06 18:23:10 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// # include "../../includes/minishell.h"
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_lexer
{
	char			*input;
	int				qouted;
	struct s_lexer	*next;
}					t_lexer;

t_lexer				*init_s_lexer(int len);
char				*free_all(t_lexer *head);
t_lexer				*new_pipe_red(char *str, char c, int *i);
int					check_next_token(t_lexer f_token, t_lexer *s_token);
int					pipe_red_dup(t_lexer *head);
void				print_error(char *str);
t_lexer				*merge_red(t_lexer *head);
int					check_red_pipe(char c);
t_lexer				*add_tokens(char *input, int i, int j);
int					check_output_red(t_lexer token, int is_next);
int					check_input_red(t_lexer token, int is_next);
t_lexer				*expand_lexer_tokens(t_lexer *lexer, t_shell shell);
void				skip_spaces(char *input, int *i);
#endif