/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:47 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/17 19:17:04 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** minishell.h
**
** This is the brain of the entire project - the header file that every
** single .c file will include. It is the contract between all parts
** of the program.
**
** What lives here:
**
**   1. ALL structs - the data structures that define how information
**      flows through the program. The lexer creates tokens, the parser
**      creates commands, the executor reads commands. They all need to
**      agree on what those things look like. That agreement lives here.
**
**   2. ALL enums - named constants like token types (WORD, PIPE, etc.)
**      so we never use magic numbers like 0, 1, 2 in our code.
**
**   3. ALL function prototypes - declarations of every function so that
**      any file can call any function without the compiler complaining.
**
**   4. ALL includes - we include system headers like <stdio.h> and
**      <readline/readline.h> once here, so every file gets them.
**
**   5. The global variable declaration - our one allowed global variable
**      for signal handling.
**
** Think of minishell.h as the dictionary of our project. Before two
** people can have a conversation, they need to agree on what words mean.
** This file is where we define what everything means.
**
** IMPORTANT: This file is included by everyone, so be careful what you
** put here. A mistake here breaks every single file in the project.
*/
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

int	g_signal;

typedef enum e_redirections_types //an enumeration for redirections
{
	redir_in, //<
	redir_out, //>
	redir_append, //>>
	redir_heredoc //<<
} t_redirections_types;

typedef struct s_redirections //a linked list of all the redirections
{
	t_redirections_types	type; //the type of the redirections
	char					*file_name; //name of the files which will be redirected to
	int						heredoc_fd;
	int						heredoc_expansion_status;
	struct s_redirections	*next; //the next node
} t_redirections;


typedef struct s_single_command
{
    int     num_args; //number of argument in the command (ex ls -la is 2 agruments)
    char    **args; //arguments of the single command (ex ["ls", "-la", NULL])
	char	**files; // maybe there is more than 1 file (ex [cat file1 file2])
	t_redirections		*redirections; //redirections linked list
}   t_single_command;

typedef struct s_command
{
	int					num_single_commands; //number of single command, could also indicate the number of pipes
	t_single_command	**commands; //2d array of the single commands
} t_command;

typedef struct S_shell
{
	char	**env;
	int		exit_status;
} t_shell;

//executor
void	free_2d(char **arr);
void	apply_redirections(t_single_command command);
char    *find_path(char *cmd, t_shell *shell);
int	array_2d_len(char **arr);
char	*env_get(char **env, char *key);
int	env_set(char ***env, char *key, char *value);
int	env_unset(char ***env, char *key);
int	builtin_cd(t_single_command	cmd,t_shell *shell);
int	builtin_echo(t_single_command cmd);
int	builtin_env(t_shell shell);
int	builtin_exit(t_single_command	cmd,t_shell *shell);
int	builtin_export(t_single_command	cmd,t_shell *shell);
int	builtin_pwd();
int builtin_unset(t_single_command cmd, t_shell *shell);
int is_builtin(char *cmd);
int execute_builtin(t_single_command *cmd, t_shell *shell);
void	handle_sigint(int sig);
void	set_interactive_signals();
void	set_execution_signals_child();
void	set_execution_signals_parent();

#endif
