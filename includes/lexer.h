/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:13:14 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/08 17:59:53 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

/*init and append tokens*/
t_lexer				*init_lexer(int len);
t_lexer				*add_tokens(char *input, int start, int end);
t_lexer				*new_operator_token(char *str, char operator, int *i);

/*functions syntax error handling*/
int					check_next_token(t_lexer f_token, t_lexer *s_token);
int					check_sec_token(t_lexer f_token, t_lexer *s_token,
	t_redirections **here);
int					check_pipe_redir_syntax(t_lexer *head);
int					check_output_red(t_lexer token, int is_next);
int					check_input_red(t_lexer token, int is_next);
int					is_input_redir(t_lexer token);
int					is_output_redir(t_lexer token);
	
/*functions for handling heredoc syntax*/
void				skip_spaces(char *input, int *i);
int					heredoc_syntax(t_lexer *head, t_redirections **here);
t_lexer				*expand_tokens(t_lexer *lexer, t_shell shell);
	
char				*clean_lexer(t_lexer *head);
int					get_char_type(char c);
void				print_error(char *str);
#endif