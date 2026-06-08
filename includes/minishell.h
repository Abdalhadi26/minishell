/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:47 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/08 18:37:51 by ahhammad         ###   ########.fr       */
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

extern int					g_signal;

typedef enum e_redirections_types
{
	redir_in,
	redir_out,
	redir_append,
	redir_heredoc
}							t_redirections_types;

typedef struct s_redirections
{
	t_redirections_types	type;
	char					*file_name;
	int						heredoc_fd;
	int						heredoc_expansion_status;
	struct s_redirections	*next;
}							t_redirections;

typedef struct s_single_command
{
	int						num_args;
	char					**args;
	t_redirections			*redirections;
}							t_single_command;

typedef struct s_command
{
	int						num_single_commands;
	t_single_command		**commands;
}							t_command;

typedef struct s_shell
{
	char					**env;
	int						exit_status;
}							t_shell;

int			read_heredoc(t_shell *shell, t_redirections *redir,
				int *pipe_fd, int saved_stdin);
void		free_2d(char **arr);
void		apply_redirections(t_single_command command);
void		execute_single(t_command *cmds,
				t_single_command command,
				t_shell *shell);
void		execute_pipeline(t_command *command,
				t_shell *shell);
void		close_all_pipes(int **pipes, int num_pipes);
void		free_pipes(int **arr, int n);
int			create_pipes(t_command command, int ***pipes);
char		*find_path(char *cmd, t_shell *shell);
int			array_2d_len(char **arr);
int			collect_heredocs(t_command *command,
				t_shell *shell);
int			env_init(t_shell *shell, char **envp);
char		*env_get(char **env, char *key);
int			env_set(char ***env, char *key, char *value);
int			env_unset(char ***env, char *key);
char		*ft_strjoin_3str(const char *s1, const char *s2,
				const char *s3);
int			extend_and_append(char ***env, char *key, char *eq,
				char *value);
int			builtin_cd(t_single_command cmd, t_shell *shell);
int			builtin_echo(t_single_command cmd);
int			builtin_env(t_shell shell);
int			builtin_exit(t_command *cmds, t_single_command cmd,
				t_shell *shell);
int			builtin_export(t_single_command cmd,
				t_shell *shell);
int			is_valid_arg(char *key);
int			builtin_pwd(void);
int			builtin_unset(t_single_command cmd, t_shell *shell);
int			is_builtin(char *cmd);
int			execute_builtin(t_command *cmds,
				t_single_command command,
				t_shell *shell);
void		handle_sigint(int sig);
void		set_interactive_signals(void);
void		set_execution_signals_child(void);
void		set_execution_signals_parent(void);
void		set_heredoc_signals(void);
void		handle_sigint_heredoc(int sig);
int			wait_exit_code(int status);
int			wait_exit_state(int status);
void		free_cmds_shell(t_command *cmds, t_shell *shell);
t_command	*main_parsing(char *input, t_shell *shell);
void		check_sigint_status(t_shell *shell);
void		close_other_heredocs(t_command *command, int i);
void		child_cleanup_exit(t_command *command, t_shell *shell,
				int **pipes, int code);
int			expand_heredoc(char *line, int *pipe_fd, int qouted,
				t_shell *shell);
int			handle_heredoc_eof(t_redirections *redir, int *pipe_fd,
				int saved_stdin);

#endif
