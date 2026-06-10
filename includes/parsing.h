/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:44:10 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/08 14:38:30 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./lexer.h"

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

/*check pipe qouted or not*/
int					pipe_not_qouted(t_lexer *tok);

/*adding arguments and files to single command*/
int					add_args_files_single_cmd(t_single_command *cmd, t_args *args,
						t_files *files);
int					add_args_files(t_lexer *tok, t_args **args, t_files **files);

/*link redirections*/
int					link_red(t_redirections **here, t_redirections *here_now);

/*cleaning functions*/
void				clean_cmds(t_command_list *cmds);
void				clean_redirections(t_redirections *redirs);
t_single_command	*clean_cmds_args_files(t_single_command *cmds, t_args *args,
						t_files *files);

/*init functions*/
t_single_command	*init_single_command(void);
t_redirections		*init_red(t_redirections_types type, t_lexer *token);
t_args				*init_arg(char *arg);

/*parsing functions*/
t_single_command	*handle_redir(t_lexer *tok, t_args *args, t_files *files);
t_single_command	*handle_word(t_lexer *tok);
t_command_list		*parsing(t_lexer *token, int num_cmds);



#endif