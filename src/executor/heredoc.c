/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:35 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/09 22:37:24 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_heredoc(t_shell *shell, t_redirections *redir, int *pipe_fd,
		int saved_stdin)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (handle_heredoc_eof(redir, pipe_fd, saved_stdin));
		if (!ft_strncmp(line, redir->file_name, ft_strlen(redir->file_name)
				+ 1))
		{
			free(line);
			return (0);
		}
		if (!expand_heredoc(line, pipe_fd, redir->heredoc_expansion_status,
				shell))
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(saved_stdin);
			return (1);
		}
	}
	return (0);
}

static int	process_one_heredoc(t_shell *shell, t_redirections *redir,
		int saved_stdin)
{
	int	pipe_fd[2];
	int	res;

	if (pipe(pipe_fd) == -1)
		return (0);
	res = read_heredoc(shell, redir, pipe_fd, saved_stdin);
	if (res != 0)
		return (res);
	close(pipe_fd[1]);
	redir->heredoc_fd = pipe_fd[0];
	return (0);
}

int	collect_heredocs(t_command_list *command, t_shell *shell)
{
	t_redirections	*redir;
	int				saved_stdin;
	int				res;
	int				i;

	saved_stdin = dup(STDIN_FILENO);
	set_heredoc_signals();
	i = 0;
	while (i < command->num_single_commands)
	{
		redir = command->commands[i]->redirections;
		while (redir)
		{
			if (redir->type == redir_heredoc)
			{
				res = process_one_heredoc(shell, redir, saved_stdin);
				if (res != 0)
					return (res);
			}
			redir = redir->next;
		}
		i++;
	}
	close(saved_stdin);
	return (0);
}
