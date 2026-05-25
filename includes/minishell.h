/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:47 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/25 16:36:55 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

static int			g_signal;

typedef enum e_redirections_types // an enumeration for redirections
{
	redir_in,     //<
	redir_out,    //>
	redir_append, //>>
	redir_heredoc //<<
}					t_redirections_types;

typedef struct s_redirections // a linked list of all the redirections
{
	t_redirections_types type; // the type of the redirections
	char *file_name;           // name of the files which will be redirected to
	int heredoc_fd;
	int heredoc_expansion_status;
	struct s_redirections *next; // the next node
}					t_redirections;

typedef struct s_single_command
{
	int				num_args;
	char			**args;
	char			**files;
	t_redirections	*redirections;
}					t_single_command;

typedef struct s_command
{
	int num_single_commands;     // number of single command,could also indicate the number of pipes
	t_single_command **commands; // 2d array of the single commands
}					t_command;

typedef struct S_shell
{
	char			**env;
	int				exit_status;
}					t_shell;

// executor
void				free_2d(char **arr);
void				apply_redirections(t_single_command command);
void				execute_single(t_single_command command, t_shell *shell);
void				execute_pipeline(t_command command, t_shell *shell);
char				*find_path(char *cmd, t_shell *shell);
int					array_2d_len(char **arr);
void				collect_heredocs(t_command *command);
int					env_init(t_shell *shell, char **envp);
char				*env_get(char **env, char *key);
int					env_set(char ***env, char *key, char *value);
int					env_unset(char ***env, char *key);
int					builtin_cd(t_single_command cmd, t_shell *shell);
int					builtin_echo(t_single_command cmd);
int					builtin_env(t_shell shell);
int					builtin_exit(t_single_command cmd, t_shell *shell);
int					builtin_export(t_single_command cmd, t_shell *shell);
int					builtin_pwd(void);
int					builtin_unset(t_single_command cmd, t_shell *shell);
int					is_builtin(char *cmd);
int					execute_builtin(t_single_command *cmd, t_shell *shell);
void				handle_sigint(int sig);
void				set_interactive_signals(void);
void				set_execution_signals_child(void);
void				set_execution_signals_parent(void);
int					wait_exit_code(int status);
int					wait_exit_state(int status);

#endif
