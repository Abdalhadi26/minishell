/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:35 by aayasrah          #+#    #+#             */
/*   Updated: 2026/04/21 16:48:58 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** heredoc.c
**
** This file handles heredocs specifically - the << redirection.
** Heredoc is complex enough to deserve its own file.
**
** What is a heredoc?
**   Heredoc (here document) lets you type multiple lines of input
**   directly in the terminal, which then get fed as stdin to a command.
**   You start it with << DELIMITER and type your input line by line.
**   When you type a line that contains ONLY the delimiter, it stops.
**
**   Example:
**     cat << EOF
**     hello
**     world
**     EOF
**   This feeds "hello\nworld\n" as stdin to cat.
**
** How we implement it:
**   When the parser sees <<, we dont execute it immediately.
**   Before any execution happens, we go through ALL heredocs in
**   the command list and collect their input first.
**   We read line by line using readline() until we see the delimiter.
**   We store all the collected input, then during execution we
**   feed it to the command as its stdin.
**
** Special behaviors to handle:
**   - ctrl-C during heredoc input should cancel it (exit status 130)
**   - ctrl-D during heredoc shows a warning like bash does
**   - Variables should expand inside heredoc UNLESS the delimiter
**     was quoted (e.g. << 'EOF' means no expansion)
**
** Think of heredoc like a temporary document you create on the spot
** and immediately hand to a command to read from.
*/

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
					if (!line)
					{
						ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
						ft_putstr_fd(redirections_list->file_name, 2);
						ft_putstr_fd("')\n",2);
						close(pipe_fd[1]);
						redirections_list->heredoc_fd = pipe_fd[0];
						return ;
					}
					if (!ft_strncmp(line, redirections_list->file_name, ft_strlen(redirections_list->file_name)))
					{
						free(line);
						break;
					}
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
