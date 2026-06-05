/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:44:10 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/03 06:39:45 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// #include "../lexer/lexer.h"
# include "../../includes/minishell.h"

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct s_files
{
	char			*files;
	struct s_files	*next;
}					t_files;

t_single_command	*init_single_command(void);
t_redirections		*init_red(t_redirections_types type, t_lexer *token);
// t_single_command *parsing_check(t_lexer *token);
t_single_command	*handle_redir(t_lexer *tok, t_args *args, t_files *files);
t_single_command	*handle_word(t_lexer *tok);
int					pipe_not_qouted(t_lexer *tok);
void				free_cmds(t_command *cmds);
t_single_command	*free_cmd_a_f(t_single_command *cmds, t_args *args,
						t_files *files);
t_command			*parsing(t_lexer *token, int num_cmds);
int					convert_args_files(t_single_command *cmd, t_args *args,
						t_files *files);
int					add_arg_file(t_lexer *tok, t_args **args, t_files **files);
t_args				*init_arg(char *arg);

#endif