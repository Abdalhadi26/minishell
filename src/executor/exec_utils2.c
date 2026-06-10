/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:30 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/08 11:25:44 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	free_cmds_shell(t_command_list *cmds, t_shell *shell)
{
	clean_cmds(cmds);
	free_2d(shell->env);
	free(shell);
}

void	close_other_heredocs(t_command_list *command, int i)
{
	int				j;
	t_redirections	*redir;

	j = 0;
	while (j < command->num_single_commands)
	{
		if (j != i)
		{
			redir = command->commands[j]->redirections;
			while (redir)
			{
				if (redir->type == redir_heredoc && redir->heredoc_fd != -1)
					close(redir->heredoc_fd);
				redir = redir->next;
			}
		}
		j++;
	}
}

void	child_cleanup_exit(t_command_list *command, t_shell *shell, int **pipes,
		int code)
{
	free_pipes(pipes, command->num_single_commands - 1);
	free_cmds_shell(command, shell);
	close(0);
	close(1);
	close(2);
	exit(code);
}
