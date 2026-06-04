/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:23:17 by aayasrah          #+#    #+#             */
/*   Updated: 2026/05/28 14:10:57 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

int	execute_builtin(t_command *cmds, int i, t_shell *shell)
{
	char	*name;
	t_single_command *single_cmd;

	cmd = cmds->commands[i];
	name = cmd->args[0];
	if (!ft_strncmp(name, "echo", 5))
		return (builtin_echo(*cmd));
	if (!ft_strncmp(name, "cd", 3))
		return (builtin_cd(*cmd, shell));
	if (!ft_strncmp(name, "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(name, "export", 7))
		return (builtin_export(*cmd, shell));
	if (!ft_strncmp(name, "unset", 6))
		return (builtin_unset(*cmd, shell));
	if (!ft_strncmp(name, "env", 4))
		return (builtin_env(*shell));
	if (!ft_strncmp(name, "exit", 5))
		return (builtin_exit(cmds,cmd, shell));
	return (1);
}
