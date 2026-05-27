/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:35 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/19 13:41:18 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc(t_redirections *redir, int *pipe_fd)
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
		//expansion could go here
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
}

void	collect_heredocs(t_command *command)
{
	int				i;
	int				pipe_fd[2];
	t_redirections	*redirections_list;

	i = 0;
	while (i < command->num_single_commands)
	{
		redirections_list = command->commands[i]->redirections;
		while (redirections_list)
		{
			if (redirections_list->type == redir_heredoc)
			{
				pipe(pipe_fd);
				if (read_heredoc(redirections_list, pipe_fd))
					return ;
				close(pipe_fd[1]);
				redirections_list->heredoc_fd = pipe_fd[0];
			}
			redirections_list = redirections_list->next;
		}
		i++;
	}
}
