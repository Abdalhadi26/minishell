/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:46:41 by ahhammad          #+#    #+#             */
/*   Updated: 2026/06/10 10:06:25 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_command_list	*init_cmd_list(int num_cmds)
{
	t_command_list	*cmd;

	cmd = malloc(sizeof(t_command_list));
	if (!cmd)
		return (NULL);
	cmd->num_single_commands = num_cmds;
	cmd->commands = malloc(sizeof(t_single_command *) * (num_cmds + 1));
	if (!cmd->commands)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_single_command	*build_cmd(t_lexer **tok)
{
	t_single_command	*cmds;

	if (tok == NULL)
		return (NULL);
	while (tok && (*tok) && pipe_not_qouted(*tok))
	{
		if (get_char_type((*tok)->input[0]) == 1 && (*tok)->qouted == 0)
		{
			cmds = handle_redir(*tok, NULL, NULL);
			if (!cmds || !cmds->redirections)
				return (clean_cmds_args_files(cmds, NULL, NULL));
		}
		else
			cmds = handle_word(*tok);
		if (!cmds)
			return (clean_cmds_args_files(cmds, NULL, NULL));
		while (*tok)
		{
			if (!(*tok)->qouted && (*tok)->input[0] == '|')
				return (cmds);
			else
				(*tok) = (*tok)->next;
		}
	}
	return (cmds);
}

int	num_args(char **args)
{
	int	i;

	if (!args || !*args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

t_command_list	*parsing(t_lexer *token, int num_cmds)
{
	int				i;
	t_lexer			*tok;
	t_command_list	*cmds;

	i = 0;
	if (!token)
		return (NULL);
	cmds = init_cmd_list(num_cmds);
	if (!cmds || !cmds->commands)
		return (NULL);
	tok = token;
	while (i < num_cmds)
	{
		cmds->commands[i] = build_cmd(&tok);
		if (!cmds->commands[i])
		{
			clean_cmds(cmds);
			break ;
		}
		cmds->commands[i]->num_args = num_args(cmds->commands[i]->args);
		if (tok)
			tok = tok->next;
		i++;
	}
	return (cmds);
}
