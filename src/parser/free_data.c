/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:12:27 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/06 18:56:00 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	free_args_files(t_args *args, t_files *files)
{
	t_args	*tmp_args;
	t_files	*tmp_files;

	while (args)
	{
		tmp_args = args;
		args = args->next;
		free(tmp_args->arg);
		free(tmp_args);
	}
	while (files)
	{
		tmp_files = files;
		files = files->next;
		free(tmp_files->files);
		free(tmp_files);
	}
}

static void	free_redirections(t_redirections *redirs)
{
	t_redirections	*tmp;

	if (!redirs)
		return ;
	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		tmp->next = NULL;
		free(tmp->file_name);
		free(tmp);
	}
	redirs = NULL;
}

static void	free_cmd(t_single_command *cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return ;
	while (cmds->args && cmds->args[i])
	{
		free(cmds->args[i]);
		i++;
	}
	if (cmds->args)
		free(cmds->args);
	free_redirections(cmds->redirections);
	free(cmds);
}

t_single_command	*free_cmd_a_f(t_single_command *cmds, t_args *args,
		t_files *files)
{
	free_args_files(args, files);
	free_cmd(cmds);
	return (NULL);
}

void	free_cmds(t_command *cmds)
{
	int	i;

	i = 0;
	if (!cmds && !cmds->commands)
		return ;
	while (cmds->commands && cmds->commands[i])
	{
		free_cmd(cmds->commands[i]);
		cmds->commands[i] = NULL;
		i++;
	}
	free(cmds->commands);
	free(cmds);
	cmds = NULL;
}
