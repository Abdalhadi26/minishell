/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:35 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/25 16:38:25 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	collect_heredocs(t_command *command)
{
	int				i;
	int				pipe_fd[2];
	char			*line;
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
				while (1)
				{
					line = readline("> ");
					if (!line) // we got ctrl-d
					{
						ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `",
							2);
						ft_putstr_fd(redirections_list->file_name, 2);
						ft_putstr_fd("')\n", 2);
						close(pipe_fd[1]);
						redirections_list->heredoc_fd = pipe_fd[0];
						return ;
					}
					if (!ft_strncmp(line, redirections_list->file_name,
							ft_strlen(redirections_list->file_name)))
					{
						free(line);
						break ;
					}
					// expansion could go here
					write(pipe_fd[1], line, ft_strlen(line));
					write(pipe_fd[1], "\n", 1);
					free(line);
				}
				close(pipe_fd[1]);
				redirections_list->heredoc_fd = pipe_fd[0];
			}
			redirections_list = redirections_list->next;
		}
		i++;
	}
}
