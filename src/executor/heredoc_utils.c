/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:35 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/09 22:36:37 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/minishell.h"

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

int	expand_heredoc(char *line, int *pipe_fd, int qouted, t_shell *shell)
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

int	handle_heredoc_eof(t_redirections *redir, int *pipe_fd, int saved_stdin)
{
	if (g_signal == SIGINT)
	{
		dup2(saved_stdin, 0);
		close(saved_stdin);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (2);
	}
	ft_putstr_fd("minishell: warning: here-document", 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(redir->file_name, 2);
	ft_putstr_fd("')\n", 2);
	close(pipe_fd[1]);
	redir->heredoc_fd = pipe_fd[0];
	close(saved_stdin);
	return (1);
}
