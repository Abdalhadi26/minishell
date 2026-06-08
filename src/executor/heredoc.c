/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:35 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/08 02:50:56 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/expander.h"

static int	has_vars(char *line)
{
	int	i;

	if (!(line))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	expand_heredoc(char *line, int *pipe_fd, int qouted, t_shell *shell)
{
	char	*new_line;

	if (!line || !pipe_fd)
		return (0);
	if (has_vars(line) && (qouted != 1 && qouted != 2))
	{
		new_line = expand_string(line, *shell, -1);
		free(line);
		if (!new_line)
			return (0);
		line = new_line;
	}
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
	free(line);
	return (1);
}

int	read_heredoc(t_shell *shell, t_redirections *redir, int *pipe_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document", 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(redir->file_name, 2);
			ft_putstr_fd("')\n", 2);
			close(pipe_fd[1]);
			redir->heredoc_fd = pipe_fd[0];
			return (1);
		}
		if (!ft_strncmp(line, redir->file_name, ft_strlen(redir->file_name)))
		{
			free(line);
			return (0);
		}
		if (!expand_heredoc(line, pipe_fd, redir->heredoc_expansion_status,
				shell))
			return (1);
	}
	return (0);
}

void	collect_heredocs(t_command *command, t_shell *shell)
{
	t_redirections	*redirections_list;
	int				pipe_fd[2];
	int				i;

	i = 0;
	while (i < command->num_single_commands)
	{
		redirections_list = command->commands[i]->redirections;
		while (redirections_list)
		{
			if (redirections_list->type == redir_heredoc)
			{
				if (pipe(pipe_fd) == -1)
					return ;
				if (read_heredoc(shell, redirections_list, pipe_fd))
					return ;
				close(pipe_fd[1]);
				redirections_list->heredoc_fd = pipe_fd[0];
			}
			redirections_list = redirections_list->next;
		}
		i++;
	}
}
