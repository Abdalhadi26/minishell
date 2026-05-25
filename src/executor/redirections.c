/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:41 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/25 16:38:41 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	use_dup2(t_redirections_types type, int fd)
{
	if (type == redir_in || type == redir_heredoc)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
}

void	apply_redirections(t_single_command command)
{
	int	fd;

	if (!command.redirections)
		return ;
	while (command.redirections)
	{
		if (command.redirections->type == redir_in) // <
			fd = open(command.redirections->file_name, O_RDONLY, 0644);
		else if (command.redirections->type == redir_out) // >
			fd = open(command.redirections->file_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (command.redirections->type == redir_append) // >>
			fd = open(command.redirections->file_name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (command.redirections->type == redir_heredoc)// << i assume this gonna have its own things sepratly
			fd = command.redirections->heredoc_fd;
		if (fd < 0)
		{
			perror("minishell");
			return ;
		}
		use_dup2(command.redirections->type, fd);
		close(fd);
		command.redirections = command.redirections->next;
	}
}
