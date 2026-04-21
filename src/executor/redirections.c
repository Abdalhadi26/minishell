/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:41 by aayasrah          #+#    #+#             */
/*   Updated: 2026/04/19 14:06:42 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** redirections.c
**
** This file handles input and output redirections.
** Redirections let the user control where a command reads from
** and writes to, instead of always using the terminal.
**
** The four types of redirections:
**
**   < filename
**     Input redirection. Instead of reading from the keyboard,
**     the command reads from a file.
**     Example: cat < file.txt  (cat reads file.txt instead of keyboard)
**
**   > filename
**     Output redirection. Instead of printing to the terminal,
**     the command writes to a file. Creates the file if it doesnt
**     exist. OVERWRITES the file if it does exist.
**     Example: echo hello > out.txt
**
**   >> filename
**     Append redirection. Like > but does not overwrite.
**     Adds new output to the end of the existing file.
**     Example: echo hello >> out.txt
**
**   << delimiter
**     Heredoc. Reads input line by line from the terminal until
**     the user types a line containing only the delimiter.
**     The collected input becomes the commands stdin.
**     Example: cat << EOF  (reads until user types EOF alone on a line)
**
** How redirections work technically:
**   We use dup2() to replace standard file descriptors.
**   dup2(fd, STDIN_FILENO) makes stdin point to our file instead.
**   dup2(fd, STDOUT_FILENO) makes stdout point to our file instead.
**   After dup2() we close the original fd since we dont need it anymore.
*/
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
		return;
	while (command.redirections)
	{
		if (command.redirections->type == redir_in) // <
			fd = open(command.redirections->file_name, O_RDONLY, 0644);
		else if (command.redirections->type == redir_out) // >
			fd = open(command.redirections->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (command.redirections->type == redir_append) // >>
			fd = open(command.redirections->file_name, O_WRONLY | O_CREAT | O_APPEND , 0644);
		else if (command.redirections->type == redir_heredoc) // << i assume this gonna have its own things sepratly
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
